cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(PICO_TOOLCHAIN_PATH /opt/gcc-arm-none-eabi/bin)
# NOTE: this must happen before project()
include(libs/pico-sdk/pico_sdk_init.cmake)

project(picolino C CXX ASM)

# set(CMAKE_C_COMPILER /opt/gcc-arm-none-eabi/bin/arm-none-eabi-gcc)
# set(CMAKE_CXX_COMPILER /opt/gcc-arm-none-eabi/bin/arm-none-eabi-g++)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 20)

set(PICO_BOARD pico_w)
set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

include_directories(libs/ael/cpp/include)

add_compile_options(
    -Wall
    -Wextra
    -Wconversion
    # -Wpedantic
    -Wshadow
    -Wdouble-promotion
    -Os
    # -Werror
    -mtune=cortex-m0plus
    )

add_subdirectory(blinky)
add_subdirectory(lis3dh)
add_subdirectory(helloworld)
add_subdirectory(hw-oled)
add_subdirectory(multicore)
