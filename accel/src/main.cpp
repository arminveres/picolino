// #include <cstdint>
// #include <cstdio>
#include <stdint.h>
#include <stdio.h>

// #include "ael/array.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "lis3dh/registers.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include "picolino_spi.h"

// static constexpr uint8_t REG_DATAX0 = 0x32;
// static constexpr double SENSITIVITY_2G = 1.0 / 256;  // (g/LSB)
// static constexpr double EARTH_GRAVITY = 9.80665;     // Earth's gravity in [m/s^2]

static float read_data(spi_inst_t *spi, const uint8_t cspin, uint8_t reg, bool isaccel);

int main() {
    // define our pins
    static constexpr uint8_t SCK_pin = 18;
    static constexpr uint8_t TX_pin = 19;
    static constexpr uint8_t RX_pin = 16;
    static constexpr uint8_t CS_pin = 17;

    // where to store the reads
    // int16_t acc_x;
    // int16_t acc_y;
    // int16_t acc_z;
    float acc_x_f;
    float acc_y_f;
    float acc_z_f;
    float temp;

    constexpr uint8_t datalen = 6;
    uint8_t data[datalen];

    // ael::array<uint8_t, 8> buffer;
    // picolino::spi spiinst(picolino::DEF, 1'000'000, SCK_pin, CS_pin, TX_pin, RX_pin);

    // init SPI
    spi_inst_t *spi_ptr = spi0;
    stdio_init_all();
    printf("Hello, world!\n");
    sleep_ms(1000);

    // init Chip Select
    gpio_init(CS_pin);
    gpio_set_dir(CS_pin, GPIO_OUT);
    gpio_put(CS_pin, 1);
    //
    // Initialize SPI port at 1 MHz
    spi_init(spi_ptr, 1000 * 1000);

    // set SPI Format
    spi_set_format(spi0,        // spi instance
                   8,           // No. bits per transfer
                   SPI_CPOL_1,  // Polarity
                   SPI_CPHA_1,  // Phase
                   SPI_MSB_FIRST);

    // Init other pins
    gpio_set_function(SCK_pin, GPIO_FUNC_SPI);
    gpio_set_function(TX_pin, GPIO_FUNC_SPI);
    gpio_set_function(RX_pin, GPIO_FUNC_SPI);

    // throwaway read to make SCK high
    reg_read(spi_ptr, CS_pin, REG_WHO_AM_I, data, 1);

    // read device id
    uint8_t id;
    int read = reg_read(spi_ptr, CS_pin, REG_WHO_AM_I, &id, 1);
    printf("got %d\n", id);
    printf("isp address 0x%x\n", id);

    if (id != WHO_AM_I) {
        while (true) {
            printf("isp address 0x%x\n", id);
            printf("should be: %d\n", WHO_AM_I);
            printf("read: %d, got %d\n", read, data[0]);
            printf("Could not communicate with LIS3DH, got %d\n", data[0]);
            sleep_ms(1000);
        }
    }

    data[0] = 0x97;
    reg_write(spi_ptr, CS_pin, REG_CTRL_REG1, data[0]);

    // NOTE: if the block data unit is activated we can read the temperature, though the problem is, that
    // we cannot clear the 'read' bit, so the Acceleration values stay the same.
    // data[0] = CTRL_REG4_BDU;
    // reg_write(spi_ptr, CS_pin, REG_CTRL_REG4, data[0]);

    data[0] = (TEMP_CFG_ADC_PD | TEMP_CFG_TEMP_EN);
    reg_write(spi_ptr, CS_pin, REG_TEMP_CFG_REG, data[0]);

    sleep_ms(2000);

    while (true) {
        acc_x_f = read_data(spi_ptr, CS_pin, REG_OUT_X_H, true);
        acc_y_f = read_data(spi_ptr, CS_pin, REG_OUT_Y_H, true);
        acc_z_f = read_data(spi_ptr, CS_pin, REG_OUT_Z_H, true);
        temp = read_data(spi_ptr, CS_pin, REG_OUT_ADC3_H, false);

        printf("TEMPERATURE: %.3f%c C\n", temp, 176);
        printf("Acceleration: \n");
        printf("X: %.3fg\n", acc_x_f);
        printf("Y: %.3fg\n", acc_y_f);
        printf("Z: %.3fg\n", acc_z_f);

        sleep_ms(500);
        // Clear terminal
        printf("\e[1;1H\e[2J");
    }
    return 0;
}

static float read_data(spi_inst_t *spi, const uint8_t cspin, uint8_t reg, bool isaccel) {
    // Read two bytes of data and store in a 16 bit data structure
    uint8_t lsb;
    uint8_t msb;
    uint16_t raw_accel;
    reg_read(spi, cspin, reg, &lsb, 1);
    reg |= 0x01;
    reg_read(spi, cspin, reg, &msb, 1);
    raw_accel = static_cast<uint16_t>((msb << 8) | lsb);

    float scaling;
    float sensitivity = .004f;

    if (isaccel) {
        scaling = 64 / sensitivity;
    } else {
        scaling = 64;
    }
    return static_cast<float>(static_cast<uint16_t>(raw_accel) / scaling);
}
