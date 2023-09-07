include_directories(includes/pico-oled)

add_library(pico-oled-main
    src/OLED_1in3_c.c)

target_link_libraries(pico-oled-main PUBLIC
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_pwm
    hardware_adc)

add_library(pico-oled-gui
    src/GUI_Paint.c)

target_link_libraries(pico-oled-gui PUBLIC
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_pwm
    hardware_adc)

add_library(pico-oled-fonts
    src/font12.c
    src/font16.c
    src/font20.c
    src/font24.c
    src/font8.c)

add_library(pico-oled-config
    src/DEV_Config.c)

target_link_libraries(pico-oled-config PUBLIC
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_pwm
    hardware_adc)
