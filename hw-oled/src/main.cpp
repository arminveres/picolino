#include <cstdint>

#include "oled-drv/includes/DEV_Config.h"
#include "oled-drv/includes/GUI_Paint.h"
#include "oled-drv/includes/OLED_1in3_c.h"
#include "oled-drv/src/fonts.h"
#include "oled_test.h"
#include "pico/time.h"

using std::uint16_t;
using std::uint8_t;

void mytest() {
    sleep_ms(1000);
    printf("OELD_test Demo\n");
    if (DEV_Module_Init() != 0) {
        printf("Init failed\n");
        while (1)
            ;
    }

    OLED_1in3_C_Init();
    OLED_1in3_C_Clear();

    constexpr auto imagesize =
        ((OLED_1in3_C_WIDTH % 8 == 0) ? (OLED_1in3_C_WIDTH / 8) : (OLED_1in3_C_WIDTH / 8 + 1)) *
        OLED_1in3_C_HEIGHT;
    uint8_t BlackImage[imagesize];

    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, OLED_1in3_C_WIDTH, OLED_1in3_C_HEIGHT, 0, WHITE);
    Paint_SelectImage(BlackImage);
    sleep_ms(500);
    Paint_Clear(BLACK);

    // printf("Drawing:page 1\r\n");
    // Paint_DrawPoint(20, 10, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    // Paint_DrawPoint(30, 10, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    // Paint_DrawPoint(40, 10, WHITE, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    // Paint_DrawLine(10, 10, 10, 20, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    // Paint_DrawLine(20, 20, 20, 30, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    // Paint_DrawLine(30, 30, 30, 40, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    // Paint_DrawLine(40, 40, 40, 50, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    // Paint_DrawCircle(60, 30, 15, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    // Paint_DrawCircle(100, 40, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    // Paint_DrawRectangle(50, 30, 60, 40, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    // Paint_DrawRectangle(90, 30, 110, 50, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    // BlackImage[0] = 0xf0;
    Paint_DrawString_EN(10, 0, "Hello there", &Font24, WHITE, BLACK);
    // 3.Show image on page1
    OLED_1in3_C_Display(BlackImage);
    DEV_Delay_ms(2000);
    Paint_Clear(BLACK);

    DEV_Module_Exit();
}

auto main() -> int {
    // OLED_1in3_C_test();
    mytest();
}
