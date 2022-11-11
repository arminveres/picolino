#include <cstdint>
#include <cstdio>

#include "common.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "pico/stdio.h"
#include "ael/array.h"

 // NOTE: Where do I find the documentation for this??
static constexpr uint8_t REG_DEVID = 0x00;
static constexpr uint8_t REG_DATAX0 = 0x32;
// Other constants
static constexpr uint8_t DEVID = 0xE5;
static constexpr double SENSITIVITY_2G = 1.0 / 256;  // (g/LSB)
static constexpr double EARTH_GRAVITY = 9.80665;     // Earth's gravity in [m/s^2]

int main() {
    // define our pins
    static constexpr uint8_t SCK_pin = 4;
    static constexpr uint8_t TX_pin = 5;
    static constexpr uint8_t RX_pin = 6;
    static constexpr uint8_t CS_pin = 7;

    ael::array<uint8_t, 8> buffer;

    // init SPI
    spi_inst_t *spi_ptr = spi0;
    stdio_init_all();

    // init Chip Select
    gpio_init(CS_pin);
    gpio_set_dir(CS_pin, GPIO_OUT);
    gpio_put(CS_pin, 1);

    // set SPI Format
    spi_set_format(spi0,        // spi instance
                   8,           // No. bits per transfer
                   SPI_CPOL_1,  // Polarity
                   SPI_CPHA_1,           // Phase
                   SPI_MSB_FIRST);

    // Init other pins
    gpio_set_function(SCK_pin, GPIO_FUNC_SPI);
    gpio_set_function(TX_pin, GPIO_FUNC_SPI);
    gpio_set_function(RX_pin, GPIO_FUNC_SPI);

    // throwaway read to make SCK high
    picolino::spi::reg_read(spi_ptr,CS_pin, REG_DEVID, buffer);
    // read device id
    picolino::spi::reg_read(spi_ptr, CS_pin, REG_DEVID, buffer);
    if (buffer[0] != DEVID) {
        printf("Could not communicate with LIS3DH\n");
    }
    // picolino::reg_write(spi_ptr, CS_pin, REG_DATAX0, buffer);
    return 0;
}
