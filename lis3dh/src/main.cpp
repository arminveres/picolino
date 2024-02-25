#include <hardware/gpio.h>
#include <hardware/spi.h>
#include <pico/stdlib.h>
#include <pico/time.h>

#include <cstdint>
#include <cstdio>
#include <cstring>

#include "ael/cpp/includes/ael/boards/pico/spi.hpp"
#include "ael/types.hpp"
#include "lis3dh/registers.h"

using namespace lis3dh;
using namespace ael::types;

/// Convert an unsigned 2 Byte to signed 16byte
///
///  @source: http://tpcg.io/NHmBRR
template <u8 numBits>
static auto convert_signed_bit(u16 inp) -> i16 {
    u16 trim = inp >> (16 - numBits);
    // printf("Assembled U16: 0x%04x\n", raw_val);

    i16 convertedValueI16;

    // Need to handle negative number
    if ((trim & (0x0001 << (numBits - 1))) == (0x0001 << (numBits - 1))) {
        convertedValueI16 = ~trim;                        // invert bits
        convertedValueI16 &= (0xFFFF >> (16 - numBits));  // but keep just the 10-bits
        convertedValueI16 += 1;                           // add 1
        convertedValueI16 *= -1;                          // multiply by -1
        // NOTE: that the last two lines could be replaced by convertedValueI16 =
        // convertedValueI16 = ~convertedValueI16;
    } else {
        // positive number, just pass it through
        convertedValueI16 = static_cast<i16>(trim);
    }
    // printf("Method #1: Converted I16: %i\n", convertedValueI16);
    // // result: -425 = 0xFE57 = [1111 1110 0101 0111]
    return convertedValueI16;
}

[[noreturn]] auto main() -> int {
    using namespace ael::boards::pico::spi;

    stdio_init_all();

    // define our pins
    static constexpr auto RX_pin = 16;
    static constexpr auto CS_pin = 17;
    static constexpr auto SCK_pin = 18;
    static constexpr auto TX_pin = 19;

    constexpr uint8_t datalen = 6;
    u8 data[datalen];

    // init SPI
    auto spi = SPI<eInstSPI::SPI_0, CS_pin, SCK_pin, TX_pin, RX_pin, 1'000'000>();

    const auto reset_lis3dh = [&spi]() {
        u8 reg[8] = {0};

        // initialize sensor completely including setting in power down mode
        spi.rwrite<8>(regs::REG_TEMP_CFG_REG, reg);
        spi.rwrite<1>(regs::REG_FIFO_CTRL_REG, reg);
        spi.rwrite<1>(regs::REG_INT1_CFG, reg);
        spi.rwrite<2>(regs::REG_INT1_THS, reg);
        spi.rwrite<1>(regs::REG_INT2_CFG, reg);
        spi.rwrite<2>(regs::REG_INT2_THS, reg);
        spi.rwrite<1>(regs::REG_CLICK_CFG, reg);
        spi.rwrite<4>(regs::REG_CLICK_THS, reg);
    };
    // reset_lis3dh();

    // throwaway read to make SCK high
    spi.rread<1>(regs::REG_WHO_AM_I, data);

    // read device id
    u8 id = 0;
    int read = spi.rread<1>(regs::REG_WHO_AM_I, &id);
    printf("SPI address 0x%x\n", id);
    sleep_ms(1000);

    if (id != regs::WHO_AM_I) {
        while (true) {
            printf("SPI address 0x%x, expected 0x%x\n", id, regs::WHO_AM_I);
            printf("read: %d, got %d\n", read, data[0]);
            printf("Could not communicate with LIS3DH, got %d\n", data[0]);
            sleep_ms(1000);
            printf("\e[1;1H\e[2J");
        }
    }

    {  /// init LIS3DH
        sleep_ms(50);

        constexpr u8 reg1 =
            (regs::RATE_10_HZ | regs::CTRL_REG1_XEN | regs::CTRL_REG1_YEN | regs::CTRL_REG1_ZEN) &
            u8(~regs::CTRL_REG1_LPEN);
        spi.rwrite<1>(regs::REG_CTRL_REG1, &reg1);

        // set High Pass Filter
        // auto val = regs::CTRL_REG2_FDS;  //| regs::CTRL_REG2_HPCLICK | ;

        constexpr u8 reg4 = regs::CTRL_REG4_BDU & u8(~regs::CTRL_REG4_HR);
        spi.rwrite<1>(regs::REG_CTRL_REG4, &reg4);

        // u8 ref;
        // spi.rread<1>(regs::REG_REFERENCE, &ref);
        // printf("ref: %02x\n", ref);

        u8 fifo_reg = (regs::FIFO_CTRL_BYPASS);
        spi.rwrite<1>(regs::REG_FIFO_CTRL_REG, &fifo_reg);

        constexpr u8 cfg_reg = (regs::TEMP_CFG_ADC_PD | regs::TEMP_CFG_TEMP_EN);
        spi.rwrite<1>(regs::REG_TEMP_CFG_REG, &cfg_reg);

        sleep_ms(50);
    }

    while (true) {
        // Clear terminal
        // printf("\e[1;1H\e[2J");

        u8 status = 0;
        if (!spi.rread<1>(regs::REG_STATUS_REG, &status)) {
            printf("ERROR while reading\n");
            continue;
        }
        // printf("Status: 0b%08b\n", status);
        if (not(status & 0b00001000)) {
            // printf("No new data\n");
            // sleep_ms(1000);
            continue;
        }

        // static u8 ldata[6] = {0};
        // spi.rread<1>(regs::REG_OUT_X_L, &ldata[0]);
        // spi.rread<1>(regs::REG_OUT_X_H, &ldata[1]);
        // spi.rread<1>(regs::REG_OUT_Y_L, &ldata[2]);
        // spi.rread<1>(regs::REG_OUT_Y_H, &ldata[3]);
        // spi.rread<1>(regs::REG_OUT_Z_L, &ldata[4]);
        // spi.rread<1>(regs::REG_OUT_Z_H, &ldata[5]);

        // for (size_t i = 0; i < 6; i++) {
        //     printf("%03d ", ldata[i]);
        // }
        // printf("\n");

        // u8 rxl, rxh, ryl, ryh, rzl, rzh;
        // spi.rread<1>(regs::REG_OUT_X_L, &rxl);
        // spi.rread<1>(regs::REG_OUT_X_H, &rxh);
        // spi.rread<1>(regs::REG_OUT_Y_L, &ryl);
        // spi.rread<1>(regs::REG_OUT_Y_H, &ryh);
        // spi.rread<1>(regs::REG_OUT_Z_L, &rzl);
        // spi.rread<1>(regs::REG_OUT_Z_H, &rzh);
        // 
        // u16 rawx = static_cast<u16>((rxh << 8) | (rxl));
        // u16 rawy = static_cast<u16>((ryh << 8) | (ryl));
        // u16 rawz = static_cast<u16>((rzl << 8) | (rzh));


        u16 rawx, rawy, rawz;
        spi.rread<2>(regs::REG_OUT_X_L, (u8*)&rawx);
        spi.rread<2>(regs::REG_OUT_Y_L, (u8*)&rawy);
        spi.rread<2>(regs::REG_OUT_Z_L, (u8*)&rawz);

        printf("RAW: x: %d, y: %d, z: %d\n", rawx, rawy, rawz);
        auto conx = convert_signed_bit<10>(rawx);
        auto cony = convert_signed_bit<10>(rawy);
        auto conz = convert_signed_bit<10>(rawz);
        printf("CON: x: %d, y: %d, z: %d\n", conx, cony, conz);

        sleep_ms(100);
        // printf("\e[1;1H\e[2J");
    }
}
