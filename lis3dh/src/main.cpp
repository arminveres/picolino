#include <hardware/gpio.h>
#include <hardware/spi.h>
#include <pico/stdlib.h>
#include <pico/time.h>

#include <cstdint>
#include <cstdio>

#include "lis3dh/registers.h"
#include "picolino_spi.h"

using namespace lis3dh;

/// Convert an unsigned 2 Byte to signed 16byte
///
///  @source: http://tpcg.io/NHmBRR
static auto conv_signed_10bit(uint16_t inp) -> int16_t {
    constexpr uint8_t numBits = 10;
    uint16_t trim = inp >> (16 - numBits);
    // printf("Assembled U16: 0x%04x\n", raw_val);

    int16_t convertedValueI16;

    // Need to handle negative number
    if ((trim & (0x0001 << (numBits - 1))) == (0x0001 << (numBits - 1))) {
        convertedValueI16 = ~trim;                        // invert bits
        convertedValueI16 &= (0xFFFF >> (16 - numBits));  // but keep just the 10-bits
        convertedValueI16 += 1;                           // add 1
        convertedValueI16 *= -1;                          // multiply by -1
        // NOTE: that the last two lines could be replaced by convertedValueI16 =
        // ~convertedValueI16;
    } else {
        // positive number, just pass it through
        convertedValueI16 = static_cast<int16_t>(trim);
    }
    // printf("Method #1: Converted I16: %i\n", convertedValueI16);
    // // result: -425 = 0xFE57 = [1111 1110 0101 0111]
    return convertedValueI16;
}

static auto read_data(spi_inst_t *spi, const uint8_t cspin, uint8_t reg) -> int16_t {
    // Read two bytes of data and store in a 16 bit data structure
    uint8_t lsb;
    uint8_t msb;
    uint16_t raw_val;

    reg_read(spi, cspin, reg, &lsb, 1);
    reg |= 0x01;
    reg_read(spi, cspin, reg, &msb, 1);
    raw_val = static_cast<uint16_t>((msb << 8) | lsb);

    return conv_signed_10bit(raw_val);
}

[[noreturn]] auto main() -> int {
    // define our pins
    static constinit uint8_t RX_pin = 16;
    static constinit uint8_t CS_pin = 17;
    static constinit uint8_t SCK_pin = 18;
    static constinit uint8_t TX_pin = 19;

    constexpr uint8_t datalen = 6;
    uint8_t data[datalen];

    // ael::array<uint8_t, 8> buffer;
    // picolino::spi spiinst(picolino::DEF, 1'000'000, SCK_pin, CS_pin, TX_pin,
    // RX_pin);

    // init SPI
    const auto spi_ptr = spi0;
    stdio_init_all();
    std::printf("Hello, world!\n");
    sleep_ms(1000);

    // init Chip Select
    gpio_init(CS_pin);
    gpio_set_dir(CS_pin, GPIO_OUT);
    gpio_put(CS_pin, 1);
    //
    // Initialize SPI port at 10 MHz
    spi_init(spi_ptr, 10000 * 1000);

    // set SPI Format
    spi_set_format(spi_ptr, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);

    // Init other pins
    gpio_set_function(SCK_pin, GPIO_FUNC_SPI);
    gpio_set_function(TX_pin, GPIO_FUNC_SPI);
    gpio_set_function(RX_pin, GPIO_FUNC_SPI);

    // throwaway read to make SCK high
    reg_read(spi_ptr, CS_pin, regs::REG_WHO_AM_I, data, 1);

    // read device id
    uint8_t id;
    int read = reg_read(spi_ptr, CS_pin, regs::REG_WHO_AM_I, &id, 1);
    // printf("got %d\n", id);
    // printf("isp address 0x%x\n", id);

    if (id != regs::WHO_AM_I) {
        while (true) {
            printf("isp address 0x%x\n", id);
            printf("should be: %d\n", regs::WHO_AM_I);
            printf("read: %d, got %d\n", read, data[0]);
            printf("Could not communicate with LIS3DH, got %d\n", data[0]);
            sleep_ms(1000);
        }
    }

    // NOTE: if the block data unit is activated we can read the temperature,
    // though the problem is, that we cannot clear the 'read' bit, so the
    // Acceleration values stay the same. data[0] = CTRL_REG4_BDU;
    // reg_write(spi_ptr, CS_pin, REG_CTRL_REG4, data[0]);

    data[0] = regs::CTRL_REG4_BDU;
    reg_write(spi_ptr, CS_pin, regs::REG_CTRL_REG4, data[0]);

    data[0] = (regs::TEMP_CFG_ADC_PD | regs::TEMP_CFG_TEMP_EN);
    reg_write(spi_ptr, CS_pin, regs::REG_TEMP_CFG_REG, data[0]);

    sleep_ms(1000);

    while (true) {
        uint8_t lsb = 0;
        uint8_t msb = 0;
        reg_read(spi_ptr, CS_pin, regs::REG_OUT_ADC3_L, &lsb, 1);
        reg_read(spi_ptr, CS_pin, regs::REG_OUT_ADC3_H, &msb, 1);
        uint16_t temp = static_cast<uint16_t>(msb << 8) | lsb;
        printf("TEMPERATURE: %hd C\n", conv_signed_10bit(temp));

        const auto acc_x_l = read_data(spi_ptr, CS_pin, regs::REG_OUT_X_L);
        const auto acc_y_l = read_data(spi_ptr, CS_pin, regs::REG_OUT_Y_L);
        const auto acc_z_l = read_data(spi_ptr, CS_pin, regs::REG_OUT_Z_L);

        printf("Acceleration: \n");
        printf("X: %d\n", acc_x_l);
        printf("Y: %d\n", acc_y_l);
        printf("Z: %d\n", acc_z_l);

        sleep_ms(250);

        // Clear terminal
        printf("\e[1;1H\e[2J");
    }
}
