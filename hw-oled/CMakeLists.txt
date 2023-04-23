add_subdirectory(../libs/oled-drv/ ../build/hw-oled)

add_executable(hioled
    src/main.cpp
    src/oled_test.c
    src/ImageData.c
    )

target_include_directories(hioled PUBLIC includes)
target_include_directories(hioled PUBLIC ../libs)

target_link_libraries(hioled
    OLED
    GUI
    Fonts
    Config
    pico_stdlib
    hardware_spi
    hardware_i2c)

# enable usb output, disable uart
pico_enable_stdio_usb(hioled 1)
pico_enable_stdio_uart(hioled 0)

pico_add_extra_outputs(hioled)
