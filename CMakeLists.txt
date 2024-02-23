cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(PICO_TOOLCHAIN_PATH /opt/gcc-arm-none-eabi/bin)
# NOTE: this must happen before project()
include(libs/pico-sdk/pico_sdk_init.cmake)

project(picolino C CXX ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 20)

set(PICO_BOARD pico_w)
# set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

set(AEL_USE_PICO_SDK true)
set(AEL_BOARD pico_w)
set(AEL_TOOLCHAIN_PATH /opt/gcc-arm-none-eabi/bin)
add_subdirectory(libs/ael)

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

add_subdirectory(blinky)
add_subdirectory(lis3dh)
add_subdirectory(helloworld)
add_subdirectory(hw-oled)
add_subdirectory(multicore)
