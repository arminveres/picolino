#include "picolino_spi.h"

#include "hardware/spi.h"

// namespace picolino {
//
// spi::spi(const e_spi_type spi, const uint32_t& baudrate, const uint8_t& SCK_PIN,
//          const uint8_t& CS_PIN, const uint8_t& TX_PIN, const uint8_t& RX_PIN)
//     : m_baudrate(baudrate),
//       m_SCK_PIN(SCK_PIN),
//       m_CS_PIN(CS_PIN),
//       m_RX_PIN(RX_PIN),
//       m_TX_PIN(TX_PIN) {
//     switch (spi) {
//         case DEF:
//             m_handle_spi = spi0;
//         default:
//             m_handle_spi = nullptr;
//     }
//
//     // init Chip Select
//     gpio_init(m_CS_PIN);
//     gpio_set_dir(m_CS_PIN, GPIO_OUT);
//     gpio_put(m_CS_PIN, 1);
//
//     spi_init(m_handle_spi, m_baudrate);
//
//     spi_set_format(m_handle_spi,        // spi instance
//                    8,           // No. bits per transfer
//                    SPI_CPOL_1,  // Polarity
//                    SPI_CPHA_1,  // Phase
//                    SPI_MSB_FIRST);
//
//     gpio_set_function(m_SCK_PIN, GPIO_FUNC_SPI);
//     gpio_set_function(m_TX_PIN, GPIO_FUNC_SPI);
//     gpio_set_function(m_RX_PIN, GPIO_FUNC_SPI);
// }
// }  // namespace picolino
static constexpr uint8_t READ_OP = 0x80;

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
    uint8_t msg = static_cast<uint8_t>(READ_OP | (mb << 6) | reg);  // construct msg
    spi_write_blocking(spi, &msg, 1);
    bytes_read = spi_read_blocking(spi, 0, buf, nbytes);
    gpio_put(cs, 1);  // set back to high -> not transmission
    return bytes_read;
}
