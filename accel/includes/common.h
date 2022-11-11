#pragma once

#include <cstdint>

#include "ael/array.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

namespace picolino {
namespace spi {

// template <size_t N>
// void reg_write(spi_inst_t *spi, const uint8_t cs, const uint8_t reg,
//                const ael::array<uint8_t, N> &buffer);

template <size_t N>
int32_t reg_read(spi_inst_t *spi, const uint8_t cs, const uint8_t reg,
                 ael::array<uint8_t, N> &buffer) {
    int32_t bytes_read = 0;
    uint8_t mb = 0;
    if (buffer.size() < 1) {
        return -1;
    } else if (buffer.size() == 1) {
        mb = 0;
    } else {
        mb = 1;
    }
    uint8_t msg = static_cast<uint8_t>(0x80 | (mb << 6) | reg);  // construct msg
    gpio_put(cs, 0);                                             // Read from req
    spi_write_blocking(spi, &msg, 1);
    bytes_read = spi_read_blocking(spi, 0, buffer.raw_ptr(), buffer.size());
    gpio_put(cs, 1);
    return bytes_read;
}

}  // namespace spi
}  // namespace picolino
