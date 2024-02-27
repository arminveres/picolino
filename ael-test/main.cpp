#include <pico/stdio.h>
#include <pico/stdlib.h>
#include <pico/time.h>

#include "ael/boards/pi_pico/extras/lis3dh.hpp"
#include "ael/boards/pi_pico/spi.hpp"
#include "ael/peripherals/lis3dh/lis3dh.hpp"
#include "ael/peripherals/lis3dh/registers.hpp"
#include "ael/types.hpp"

using namespace ael::types;
using namespace ael::boards::pi_pico::spi;
using namespace ael::boards::pi_pico::extras::lis3dh;

[[noreturn]] int main() {
    stdio_init_all();

    auto spi = SPI(eInstSPI::SPI_0, 17, 18, 19, 16, 1'000'000);
    auto accm = LIS3DH(spi);

    while (true) {
        printf("hello\n");
        sleep_ms(500);
    }

    if (const auto id = accm.reg_read(reg_addr::WHO_AM_I); id.has_value()) {
        printf("SPI address 0x%x\n", *id);
    } else if (id.error() == eError::FAIL or id.error() == eError::OHTER) {
        // printf("ERROR: SPI address 0x%x, expected 0x%x\n", id, regs::WHO_AM_I);
        printf("ERROR: Expected Address 0x%x\n", reg_addr::WHO_AM_I);
        while (true) {
            sleep_us(10'000);
        }
    }

    while (true) {
        // reg_status status;
        auto status = accm.reg_read(reg_addr::STATUS);
        printf("Status: 0b%08b\n", status);
        if (const auto prot_accel = accm.read_accel(); prot_accel.has_value()) {
            const auto accel = *prot_accel;
            printf("CON: x: %d, y: %d, z: %d\n", accel.x, accel.y, accel.z);
        }
    }
}
