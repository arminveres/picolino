#include "pico/multicore.h"
#include "pico/stdlib.h"

auto entry_core_one() {
    while (true) {
    }
}

auto main() -> int { multicore_launch_core1(entry_core_one); }
