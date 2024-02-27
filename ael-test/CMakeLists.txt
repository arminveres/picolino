add_executable(ael-accel
    main.cpp
)

target_link_libraries(ael-accel PUBLIC
    ael
)

# enable usb output, disable uart
pico_enable_stdio_usb(ael-accel 1)
pico_enable_stdio_uart(ael-accel 0)

pico_add_extra_outputs(ael-accel)
