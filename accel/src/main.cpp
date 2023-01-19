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

static constexpr uint8_t READ_OP = 0x80;

// static constexpr uint8_t REG_DATAX0 = 0x32;
// static constexpr double SENSITIVITY_2G = 1.0 / 256;  // (g/LSB)
// static constexpr double EARTH_GRAVITY = 9.80665;     // Earth's gravity in [m/s^2]

void reg_write(spi_inst_t *spi, const uint cs, const uint8_t reg, const uint8_t data) {
    uint8_t msg[2];

    // Construct message (set ~W bit low, MB bit low)
    msg[0] = 0x00 | reg;
    msg[1] = data;

    // Write to register
    gpio_put(cs, 0);
    spi_write_blocking(spi, msg, 2);
    gpio_put(cs, 1);
}

int32_t reg_read(spi_inst_t *spi, const uint8_t cs, uint8_t reg, uint8_t *buf,
                 const uint8_t nbytes) {
    int32_t bytes_read = 0;
    uint8_t mb = 0;
    if (nbytes < 1) {
        return -1;
    } else if (nbytes == 1) {
        mb = 0;
    } else {
        mb = 1;
    }
    gpio_put(cs, 0);  // set chip select to low, to indicate transmission
    // uint8_t msg = static_cast<uint8_t>(reg | READ_OP);  // construct msg
    // uint8_t msg = static_cast<uint8_t>(READ_OP | (mb << 6) | reg);  // construct msg
    // spi_write_blocking(spi, &msg, 1);
    reg |= READ_OP;
    spi_write_blocking(spi, &reg, 1);
    sleep_ms(10);
    bytes_read = spi_read_blocking(spi, 0, buf, nbytes);
    gpio_put(cs, 1);  // set back to high -> not transmission
    sleep_ms(10);
    return bytes_read;
}
int main() {
    // define our pins
    static constexpr uint8_t SCK_pin = 18;
    static constexpr uint8_t TX_pin = 19;
    static constexpr uint8_t RX_pin = 16;
    static constexpr uint8_t CS_pin = 17;

    // where to store the reads
    int16_t acc_x;
    int16_t acc_y;
    int16_t acc_z;
    float acc_x_f;
    float acc_y_f;
    float acc_z_f;

    constexpr uint8_t datalen = 6;
    uint8_t data[datalen];

    // ael::array<uint8_t, 8> buffer;

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
    spi_init(spi_ptr, 500 * 1000);

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
    } else {
        while (true) {
            printf("isp address 0x%x\n", id);
        }
    }

    // reg_read(spi_ptr, CS_pin, regpo)
    return 0;
}
