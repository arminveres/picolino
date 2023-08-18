#include <pico/stdlib.h>

#include <array>
#include <cstdint>

static constexpr uint8_t LED_PIN = 28;

[[noreturn]] auto main() -> int {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(1000);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }
}
