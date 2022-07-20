//https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf

#pragma once

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <stdint.h>

/*COMMANDS*/

/*
 * Set Memory Addressing Mode
 * Param:
 * 0x00 Horizontal Addressing Mode
 * 0x01 Vertical Addressing Mode
 * 0x10 Page Addressing Mode
 * */
#define OLED_SSD1306_MEMORYMODE 0x20

/*
 * Set Column Address and Page Address
 * */
#define OLED_SSD1306_COLUMNADDR 0x21
#define OLED_SSD1306_PAGEADDR 0x22

/*
 * Set Screen Contrast
 * Param:
 * Byte contrast
 * */
#define OLED_SSD1306_SETCONTRAST 0x81

/*
 * Enable Charge Pump
 * Param:
 * Value
 * */
#define OLED_SSD1306_CHARGEPUMP 0x8D

/*
 * Invert Screen Horizontal
 * */
#define OLED_SSD1306_SEGMIRMAP 0xA0
#define OLED_SSD1306_SEGREMAP 0xA1

/*
 * Use GDDRAM or Not
 * */
#define OLED_SSD1306_DISPLAYALLON_RESUME 0xA4
#define OLED_SSD1306_DISPLAYALLON 0xA5

/*
 * Invert Screen Colors or Not
 * */
#define OLED_SSD1306_NORMALDISPLAY 0xA6
#define OLED_SSD1306_INVERTDISPLAY 0xA7

/*
 * Set multiplex Ratio To (1/64)
 * */
#define OLED_SSD1306_SETMULTIPLEX 0xA8

/*
 * Turn Screen On/Off
 * */
#define OLED_SSD1306_DISPLAYOFF 0xAE
#define OLED_SSD1306_DISPLAYON 0xAF

/*
 * Set Screen Mirror Verticall
 * */
#define OLED_SSD1306_COMSCANINC 0xC0
#define OLED_SSD1306_COMSCANDEC 0xC8

/*
 * Set Display Offset
 * Param:
 * Byte Offset (0)
 * */
#define OLED_SSD1306_SETDISPLAYOFFSET 0xD3

/*
 * Set Clock Prescaler
 * Param:
 * Byte Prescaler
 * */
#define OLED_SSD1306_SETDISPLAYCLOCKDIV 0xD5

/*
 * Set Precharge Period
 * Param:
 * Byte value (0x22)
 * */
#define OLED_SSD1306_SETPRECHARGE 0xD9

/*
 * Set Com Pins Hardware Config
 * Param:
 * Byte Value
 * */
#define OLED_SSD1306_SETCOMPINS 0xDA

/*
 * Set Vcomh
 * Param:
 * Byte Value
 * */
#define OLED_SSD1306_SETVCOMDETECT 0xDB

/*
 * Set Columns Addresses
 * */
#define OLED_SSD1306_SETLOWCOLUMN 0x00
#define OLED_SSD1306_SETHIGHCOLUMN 0x10

/*
 * Set Start Line Address
 * */
#define OLED_SSD1306_SETSTARTLINE 0x40

/*
 * Power modes
 * */
#define OLED_SSD1306_EXTERNALVCC 0x01
#define OLED_SSD1306_SWITCHCAPVCC 0x02

/*
 * Setting up scrolling
 * */
#define OLED_SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define OLED_SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define OLED_SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define OLED_SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A
#define OLED_SSD1306_DEACTIVATE_SCROLL 0x2E
#define OLED_SSD1306_ACTIVATE_SCROLL 0x2F
#define OLED_SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3

/*COLORS*/
#define WHITE 0
#define BLACK 1
#define INVERSE 2

int8_t OLED_1306_SendCmd(uint8_t cmd);
int8_t OLED_1306_FillScreen(uint8_t color);
int8_t OLED_1306_Init(i2c_inst_t* hi2c, uint16_t addr, uint16_t w, uint8_t h, uint8_t inv);
int8_t OLED_1306_Deinit();
int8_t OLED_1306_Display();
int8_t OLED_1306_DrawPixel(int16_t x, int16_t y, uint16_t color);
int8_t OLED_1306_DrawHorLine(uint8_t sx, uint8_t sy, uint8_t ex, uint8_t color);
int8_t OLED_1306_DrawVerLine(uint8_t sx, uint8_t sy, uint8_t ex, uint8_t color);
int8_t OLED_1306_DrawRectangle(uint8_t sx, uint8_t sy, uint8_t ex, uint8_t ey, uint8_t color, uint8_t fill_color);
int8_t OLED_1306_DrawCharacter(uint16_t x, uint16_t y, char chr, uint8_t font_size, uint8_t color);
int8_t OLED_1306_DrawString(int x, int y, const char* str, uint8_t font_size, uint8_t color);
int8_t OLED_1306_InvertColors();
int8_t OLED_1306_InvertVertically();
int8_t OLED_1306_InvertHorizontally();
