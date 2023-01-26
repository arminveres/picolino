include_directories(includes)

add_library(OLED
    src/OLED_1in3_c.c)

target_link_libraries(OLED PUBLIC
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_pwm
    hardware_adc)

add_library(GUI
    src/GUI_Paint.c)

target_link_libraries(GUI PUBLIC
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_pwm
    hardware_adc)

add_library(Fonts
    src/font12.c
    src/font12CN.c
    src/font16.c
    src/font20.c
    src/font24.c
    src/font24CN.c
    src/font8.c)

add_library(Config
    src/DEV_Config.c)

target_link_libraries(Config PUBLIC
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_pwm
    hardware_adc)
