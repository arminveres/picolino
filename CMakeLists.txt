cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

include(libs/ael/external/pico-sdk/pico_sdk_init.cmake)

# NOTE(aver): setup of pico-sdk and other important libs before the project init
set(AEL_USE_PICO_SDK true)
set(AEL_BOARD pico_w)
set(AEL_TOOLCHAIN_PATH /opt/gcc-arm-none-eabi)
add_subdirectory(libs/ael)

project(picolino
    LANGUAGES C CXX ASM
    VERSION 0.1.0
)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

pico_sdk_init()


add_compile_options(
    # -Werror
    -Wall
    -Wextra
    -Wconversion
    -Wpedantic
    # note covered by above
    -Wshadow
    -Wundef
    -Wdouble-promotion
    -Os
    -mtune=cortex-m0plus
    -fno-common
    -fstack-usage
    -ffunction-sections
    -fdata-sections
)

add_link_options(
    -Wl,-gc-sections
    -Wl,-print-memory-usage
)
# add_subdirectory(blinky)
# add_subdirectory(helloworld)
# add_subdirectory(hw-oled)
# add_subdirectory(multicore)
# add_subdirectory(lis3dh)
add_subdirectory(timer)
