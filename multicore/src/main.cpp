#include "pico/multicore.h"
#include "pico/stdlib.h"

[[noreturn]] auto entry_core_one() {
    while (true) {
    }
}

[[noreturn]] auto main() -> int { multicore_launch_core1(entry_core_one); }
