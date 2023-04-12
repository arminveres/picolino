set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_executable(multicore
    src/main.cpp)

target_include_directories(accel PUBLIC includes)
target_include_directories(accel PUBLIC ../libs)

target_link_libraries(multicore
    pico_stdlib
    pico_multicore)

# enable usb output, disable uart
# pico_enable_stdio_usb(accel 1)
# pico_enable_stdio_uart(accel 0)

pico_add_extra_outputs(multicore)
