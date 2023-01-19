# picolino

Playground for the Raspberry Pi Pico W

## LEDs

Common LED should not be driven with a higher amperage than 0.023(Pico has 3.3V on it's GPIO pins,
meaning it would be best to have a 143 OHM resistance.

## Dependencies

requires arm GNU Toolchain

I recommend to install [picotool](https://github.com/raspberrypi/picotool), which is quite nice to 
work with.

### Fedora

Get toolchain: https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads

### Ubuntu

`sudo apt install gcc-arm-none-eabi libstdc++-arm-none-eabi libnewlib-arm-none-eabi`

## Building

1. Clone recursively with flag `--recursive` to include pico-sdk
2. `cd picolino`
3. `mkdir build`
4. `cd build`
5. `cmake ..`
6. `make`

## TODO
