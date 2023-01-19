#ifndef PICOLINO_SPI_H_
#define PICOLINO_SPI_H_

#include <cstdint>

#include "ael/array.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

// Write 1 byte to the specified register
void reg_write(spi_inst_t *spi, const uint cs, const uint8_t reg, const uint8_t data);

int32_t reg_read(spi_inst_t *spi, const uint8_t cs, const uint8_t reg, uint8_t *buf,
                 const uint8_t nbytes);

#endif  // !PICOLINO_SPI_H_
