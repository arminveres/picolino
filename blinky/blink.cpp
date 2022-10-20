#include <cstdint>
#include <pico/stdlib.h>
#include <array>

int main(int argc, char *argv[]) {
  std::array<int, 10> test;
  test[0] = 6;
  static constexpr uint8_t LED_PIN = 28;
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  while (true) {
    gpio_put(LED_PIN, 1);
    sleep_ms(1000);
    gpio_put(LED_PIN, 0);
    sleep_ms(250);
  }
  return 0;
}
