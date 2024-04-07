add_executable(timer
    src/main.cpp
)

target_link_libraries(timer
    ael_main
    ael_boards_pi_pico

    pico_stdlib
    # pico_time
    # hardware_timer
)

# enable usb output, disable uart
pico_enable_stdio_usb(timer 1)
# pico_enable_stdio_uart(timer 0)

pico_add_extra_outputs(timer)
