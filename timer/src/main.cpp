#include <hardware/timer.h>
#include <pico/platform.h>
#include <pico/stdio.h>
#include <pico/stdlib.h>
#include <pico/time.h>

#include <cstdio>
#include <tuple>

#include "ael/boards/pi_pico/timer.hpp"
#include "ael/types.hpp"

using namespace ael::types;
using namespace ael::boards::pi_pico;

int main(int argc, char *argv[]) {
    stdio_init_all();
    auto timer1 = timer::Timer<timer::eTimeType::eSec>();
    timer1.start();
    printf("Hello there\n");
    printf("goodbye!\n");
    const auto endval = timer1.stop();
    printf("%llu\n", endval);

    while (1) {
        timer1.start();
        const auto triple = timer1.get_triple();
        printf("[ %02llu:%02llu:%02llu ]\n",
               std::get<0>(triple),
               std::get<1>(triple),
               std::get<2>(triple));
    }
}
