#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

#include "OLED_SSD1306.h"

int main() {
    stdio_init_all();
    
    //init i2c0
    i2c_init(i2c1, 100 * 1000);
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_pull_up(14);
    gpio_pull_up(15);
    bi_decl(bi_2pins_with_func(14, 15, GPIO_FUNC_I2C));
    
    OLED_1306_Init(i2c1, 0x3C, 128, 64, 0);
    OLED_1306_DrawPixel(1, 1, WHITE);
    OLED_1306_Display();

    sleep_ms(2000);

    OLED_1306_FillScreen(WHITE);
    OLED_1306_Display();

    sleep_ms(2000);

    OLED_1306_FillScreen(BLACK);
    OLED_1306_Display();

    OLED_1306_DrawHorLine(20, 20, 69, WHITE);
    OLED_1306_DrawVerLine(75, 10, 58, WHITE);
    OLED_1306_Display();

    sleep_ms(2000);

    OLED_1306_FillScreen(BLACK);
    OLED_1306_Display();

    OLED_1306_DrawRectangle(10, 10, 40, 40, WHITE, BLACK);
    OLED_1306_Display();

    sleep_ms(2000);

    OLED_1306_FillScreen(BLACK);
    OLED_1306_Display();

    OLED_1306_DrawCharacter(20, 20,'A', 1, WHITE);
    OLED_1306_DrawString(40, 40, "ASD", 2, WHITE);
    OLED_1306_Display();

    sleep_ms(2000);

    OLED_1306_FillScreen(BLACK);
    OLED_1306_Display();

    //rose
    OLED_1306_DrawRectangle(56, 10, 60, 14, WHITE, BLACK);
    OLED_1306_DrawRectangle(61, 10, 65, 14, WHITE, BLACK);
    OLED_1306_DrawRectangle(66, 10, 70, 14, WHITE, BLACK);
    OLED_1306_DrawRectangle(56, 15, 60, 19, WHITE, BLACK);
    OLED_1306_DrawRectangle(61, 15, 65, 19, WHITE, BLACK);
    OLED_1306_DrawRectangle(66, 15, 70, 19, WHITE, BLACK);
    OLED_1306_DrawRectangle(56, 20, 60, 24, WHITE, BLACK);
    OLED_1306_DrawRectangle(61, 20, 65, 24, WHITE, BLACK);
    OLED_1306_DrawRectangle(66, 20, 70, 24, WHITE, BLACK);
    OLED_1306_DrawRectangle(61, 25, 65, 29, WHITE, BLACK);
    OLED_1306_DrawHorLine(55, 35, 72, WHITE);
    OLED_1306_DrawHorLine(58, 42, 69, WHITE);
    OLED_1306_DrawVerLine(63, 30, 60, WHITE);

    OLED_1306_Display();

    while(1){

    }
}
