cmake_minimum_required(VERSION 3.12)

set(PICO_TOOLCHAIN_PATH /opt/gcc-arm-none-eabi/bin)
# NOTE: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)

project(picolino C CXX ASM)

# set(CMAKE_C_COMPILER /opt/gcc-arm-none-eabi/bin/arm-none-eabi-gcc)
# set(CMAKE_CXX_COMPILER /opt/gcc-arm-none-eabi/bin/arm-none-eabi-g++)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(PICO_BOARD pico_w)
set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

add_compile_options(
    -Wall
    -Os
    )

add_subdirectory(blinky)
