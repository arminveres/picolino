add_executable(blink
    blink.cpp
)

target_link_libraries(blink pico_stdlib)

pico_add_extra_outputs(blink)
