add_executable(hioled
    src/main.cpp
    src/oled_test.c
    src/ImageData.c
)


# We add the subdirectories, as otherwise cmake does not find the files
add_subdirectory(../libs/pico-oled ../build/hw-oled)

target_include_directories(hioled PUBLIC includes)
target_include_directories(hioled PUBLIC ../libs/pico-oled/includes/)
target_include_directories(hioled PUBLIC ../libs/ael/cpp/includes/)


target_link_libraries(hioled
    pico_stdlib
    hardware_spi
    hardware_i2c
    # oled driver
    pico-oled-main
    pico-oled-gui
    pico-oled-fonts
    pico-oled-config
)

# enable usb output, disable uart
pico_enable_stdio_usb(hioled 1)
pico_enable_stdio_uart(hioled 0)

pico_add_extra_outputs(hioled)
