#include "OLED_SSD1306.h"
#include "OLED_SSD1306_Font.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"

uint8_t background = BLACK;
uint8_t invertVer = 0;
uint8_t invertHor = 0;
uint8_t init = 0;
uint8_t invertColors = 0;
uint16_t width = 0;
uint16_t height = 0;
uint8_t* frame = NULL;
uint8_t oled_address = 0;
i2c_inst_t* oled_hi2c;

int8_t OLED_1306_InvertHorizontally(){
	if(invertHor == 0){
		invertHor = 1;
		return OLED_1306_SendCmd(OLED_SSD1306_SEGMIRMAP);
	}
	else{
		invertHor = 0;
		return OLED_1306_SendCmd(OLED_SSD1306_SEGREMAP);
	}
}

int8_t OLED_1306_InvertVertically(){
	if(invertVer == 0){
		invertVer = 1;
		return OLED_1306_SendCmd(OLED_SSD1306_COMSCANINC);
	}
	else{
		invertVer = 0;
		return OLED_1306_SendCmd(OLED_SSD1306_COMSCANDEC);
	}
}

int8_t OLED_1306_InvertColors(){
	if(background == BLACK){
		background = WHITE;
		return OLED_1306_SendCmd(OLED_SSD1306_INVERTDISPLAY);
	}
	else{
		background = BLACK;
		return OLED_1306_SendCmd(OLED_SSD1306_NORMALDISPLAY);
	}
}

int8_t OLED_1306_DrawString(int x, int y, const char* str, uint8_t font_size, uint8_t color){
	int8_t status = 0;

	int x_tmp = x;
	char c;
	c = *str;
	while(*str++)
	{
		status |= OLED_1306_DrawCharacter(x_tmp, y, c, font_size, color);
		x_tmp += ((uint8_t)font[1] * font_size) + 1;

		c = *str;
	}

	return status;
}

int8_t OLED_1306_DrawCharacter(uint16_t x, uint16_t y, char chr, uint8_t font_size, uint8_t color){
	if(chr > 0x7E) return 255; // chr > '~'

	int8_t status = 0;

	for(uint8_t i=0; i<font[1]; i++ )
	{
        uint8_t line = (uint8_t)font[(chr-0x20) * font[1] + i + 2];

        for(int8_t j=0; j<font[0]; j++, line >>= 1)
        {
            if(line & 1)
            {
            	if(font_size == 1)
            		status |= OLED_1306_DrawPixel(x+i, y+j, color);
            	else
            		status |= OLED_1306_DrawRectangle(x+i*font_size, y+j*font_size, x+i*font_size+font_size, y+j*font_size+font_size, color, color);
            }
        }
    }

	return status;
}

int8_t OLED_1306_DrawRectangle(uint8_t sx, uint8_t sy, uint8_t ex, uint8_t ey, uint8_t color, uint8_t fill_color){
	int8_t status = 0;

	status |= OLED_1306_DrawHorLine(sx, sy, ex, color); //top
	status |= OLED_1306_DrawHorLine(sx, ey, ex, color); //bottom

	status |= OLED_1306_DrawVerLine(sx, sy, ey, color); //left
	status |= OLED_1306_DrawVerLine(ex, sy, ey+1, color); //right

	//fill
	for(uint16_t i = sy+1; i<ey;i++){
		status |= OLED_1306_DrawHorLine(sx+1, i, ex, fill_color);
	}

	return status;
}

int8_t OLED_1306_DrawHorLine(uint8_t sx, uint8_t sy, uint8_t ex, uint8_t color){
	int8_t status = 0;

	for(uint32_t i = sx;i<ex;i++){
		status |= OLED_1306_DrawPixel(i, sy, color);
	}

	return status;
}

int8_t OLED_1306_DrawVerLine(uint8_t sx, uint8_t sy, uint8_t ey, uint8_t color){
	int8_t status = 0;

	for(uint32_t i = sy;i<ey;i++){
		status |= OLED_1306_DrawPixel(sx, i, color);
	}

	return status;
}

int8_t OLED_1306_FillScreen(uint8_t color){
	if(frame == NULL) return 255;

	memset(frame, color == BLACK ? 0 : 255, width*((height + 7) / 8));

	return 0;
}

int8_t OLED_1306_Init(i2c_inst_t* hi2c, uint16_t addr, uint16_t w, uint8_t h, uint8_t inv){
	if(init == 1) return -1;

	int8_t status = 0;

	inv = invertColors;
	oled_hi2c = hi2c;
	oled_address = addr;
	width = w;
	height = h;

	frame = (uint8_t*)malloc(width*((height + 7) / 8));

	if (frame == NULL) return -1;

	status |= OLED_1306_FillScreen(BLACK);

	/*Init Procedure*/
	status |= OLED_1306_SendCmd(OLED_SSD1306_DISPLAYOFF);

	status |= OLED_1306_SendCmd(OLED_SSD1306_MEMORYMODE);
	status |= OLED_1306_SendCmd(0x0);
	status |= OLED_1306_SendCmd(0xB0);
	status |= OLED_1306_SendCmd(OLED_SSD1306_COMSCANDEC);
	status |= OLED_1306_SendCmd(OLED_SSD1306_SEGREMAP);

	status |= OLED_1306_SendCmd(OLED_SSD1306_SETLOWCOLUMN);
	status |= OLED_1306_SendCmd(OLED_SSD1306_SETHIGHCOLUMN);
	status |= OLED_1306_SendCmd(OLED_SSD1306_SETSTARTLINE);

	status |= OLED_1306_SendCmd(OLED_SSD1306_SETCONTRAST);
	status |= OLED_1306_SendCmd(0xFF); //contrast

	if(invertColors)
		status |= OLED_1306_SendCmd(OLED_SSD1306_INVERTDISPLAY);
	else
		status |= OLED_1306_SendCmd(OLED_SSD1306_NORMALDISPLAY);

	status |= OLED_1306_SendCmd(OLED_SSD1306_SETMULTIPLEX);
	if(height == 128 || height == 64)
		status |= OLED_1306_SendCmd(0x3F);
	else
		status |= OLED_1306_SendCmd(0x1F);

	//status |= OLED_1306_SendCmd(OLED_SSD1306_DISPLAYALLON);
	status |= OLED_1306_SendCmd(OLED_SSD1306_DISPLAYALLON_RESUME);

	status |= OLED_1306_SendCmd(OLED_SSD1306_SETCOMPINS);
	if(height == 128 || height == 64)
		status |= OLED_1306_SendCmd(0x12);
	else
		status |= OLED_1306_SendCmd(0x02);

	status |= OLED_1306_SendCmd(OLED_SSD1306_SETDISPLAYOFFSET);
	status |= OLED_1306_SendCmd(0x0);

	status |= OLED_1306_SendCmd(OLED_SSD1306_SETDISPLAYCLOCKDIV);
	status |= OLED_1306_SendCmd(0x20); //clock div

	status |= OLED_1306_SendCmd(OLED_SSD1306_SETPRECHARGE);
	status |= OLED_1306_SendCmd(0x22);

	status |= OLED_1306_SendCmd(OLED_SSD1306_SETVCOMDETECT);
	status |= OLED_1306_SendCmd(0x20);

	status |= OLED_1306_SendCmd(OLED_SSD1306_CHARGEPUMP);
	status |= OLED_1306_SendCmd(0x14);

	status |= OLED_1306_SendCmd(OLED_SSD1306_DISPLAYON);

	status |= OLED_1306_Display();

	init = 1;
	if(status == 0) return status;

	OLED_1306_Deinit();
	return status;
}

int8_t OLED_1306_Deinit(){
	if(frame == NULL)
		return 255;

	free(frame);

	init = 0;
	return 0;
}

int8_t OLED_1306_DrawPixel(int16_t x, int16_t y, uint16_t color){
	if ((x >= 0) && (x < width) && (y >= 0) && (y < height)){
		if(color == WHITE){
			frame[x + (y / 8) * width] |= (1 << (y & 7));
		}
		else if(color == BLACK){
			frame[x + (y / 8) * width] &= ~(1 << (y & 7));
		}
		else if(color == INVERSE){
			frame[x + (y / 8) * width] ^= (1 << (y & 7));
		}
		else{
			return 255;
		}
		return 0;
	}
	return 255;
}

int8_t OLED_1306_Display(){
	int8_t status = 0;

	for(uint8_t i = 0; i < height/8; i++) {
		status |= OLED_1306_SendCmd(0xB0+i);
		status |= OLED_1306_SendCmd(0x00);
		status |= OLED_1306_SendCmd(0x10);
		uint8_t* temp = malloc(width+1);
		temp[0] = 0x40;
		memcpy(temp+1, &(frame[width*i]), width);
    	status |= !i2c_write_blocking(oled_hi2c, oled_address, temp, width+1, false); //0x40

		free(temp);
	}

	return status;
}

int8_t OLED_1306_SendCmd(uint8_t cmd){
	int8_t status = 0;

	uint8_t buf[2] = {0x00, cmd};
    status = i2c_write_blocking(oled_hi2c, oled_address, buf, 2, false);
	
	return status > 0 ? 0 : status;
}


