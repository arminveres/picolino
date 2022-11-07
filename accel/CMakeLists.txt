set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_executable(accel
    src/main.cpp
    )
target_include_directories(accel PUBLIC includes)

target_link_libraries(accel pico_stdlib hardware_spi)
pico_add_extra_outputs(accel)
