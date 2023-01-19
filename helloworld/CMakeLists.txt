set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_executable(hello_usb
    hello_usb.cpp
    )

target_link_libraries(hello_usb pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(hello_usb 1)
pico_enable_stdio_uart(hello_usb 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(hello_usb)
