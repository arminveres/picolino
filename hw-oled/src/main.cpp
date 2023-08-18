#include <pico/time.h>

#include <cstdint>

#include "oled-drv/includes/DEV_Config.h"
#include "oled-drv/includes/GUI_Paint.h"
#include "oled-drv/includes/OLED_1in3_c.h"
#include "oled-drv/src/fonts.h"

using u8 = std::uint8_t;

auto mytest() -> void {
    sleep_ms(1000);
    printf("OELD_test Demo\n");
    if (DEV_Module_Init() != 0) {
        printf("Init failed\n");
        while (1)
            ;
    }

    OLED_1in3_C_Init();
    OLED_1in3_C_Clear();

    static constexpr auto imagesize =
        ((OLED_1in3_C_WIDTH % 8 == 0) ? (OLED_1in3_C_WIDTH / 8) : (OLED_1in3_C_WIDTH / 8 + 1)) *
        OLED_1in3_C_HEIGHT;
    u8 BlackImage[imagesize];

    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, OLED_1in3_C_WIDTH, OLED_1in3_C_HEIGHT, 0, WHITE);
    Paint_SelectImage(BlackImage);
    sleep_ms(500);
    Paint_Clear(BLACK);
    Paint_DrawString_EN(10, 0, "Hello there", &Font24, WHITE, BLACK);
    // 3.Show image on page1
    OLED_1in3_C_Display(BlackImage);
    DEV_Delay_ms(2000);
    Paint_Clear(BLACK);

    DEV_Module_Exit();
}

auto main() -> int { mytest(); }
