/****************************************************************
*
*
* SSD1306 Driver for CH32V00X
* Created by Ign555
* Version : 0.9 v
* File Creation : 30/03/2025
*
*
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ch32v00x_gpio.h"
#include "ch32v00x_i2c.h"

#ifndef __SSD1306_H__
#define __SSD1306_H__

/****************************************************************
*
* SSD1306 command value
*
****************************************************************/

//I2C register selection
#define SSD1306_COMMAND_FLAG 0x00
#define SSD1306_DATA_FLAG 0x40

//SSD1306 pages and column
#define SSD1306_COLUMNS 128
#define SSD1306_PAGES 8

//SSD1306 screen height
#define SSD1306_32_PX 32
#define SSD1306_64_PX 64

//SSD1306 display On/Off
#define SSD1306_TURN_OFF_SCREEN 0xAE
#define SSD1306_TURN_ON_SCREEN  0xAF

//SSD1306 charge pump On/Off
#define SSD1306_DISABLE_CHARGE_PUMP 0x10
#define SSD1306_ENABLE_CHARGE_PUMP 0x14

//SSD1306 display mode
#define SSD1306_DISPLAY_MODE_NORMAL 0xA4
#define SSD1306_DISPLAY_MODE_INVERT 

//SSD1306 display scrolling
#define SSD1306_SCROLLING_ENABLE
#define SSD1306_SCROLLING_DISABLE 0x2E

//SSD1306 set display start line
#define SSD1306_START_LINE_0 0x40

//SSD1306 addressing mode
#define SSD1306_HORIZONTAL_ADDRESSING_MODE 0x00

//SSD1306 segment remap
#define SSD1306_INVERSE_SCREEN_HORIZONTAL 0xA1
#define SSD1306_INORMAL_SCREEN_HORIZONTAL 0xA0
#define SSD1306_INVERSE_SCREEN_VERTICAL 0xC8
#define SSD1306_INORMAL_SCREEN_VERTICAL 0xC0

//SSD1306 hardware configuration
//(To be add)

//SSD1306 display settings value
#define SSD1306_CHARGE_PUMP_SETTINGS 0x8D
#define SSD1306_SET_MULTIPLEX_RATIO 0xA8
#define SSD1306_SET_DISPLAY_OFFSET 0xD3
#define SSD1306_SET_CLOCK_DIVIDE_RATIO 0xD5
#define SSD1306_SET_ADDRESSING_MODE 0x20
#define SSD1306_SET_CONTRAST 0x81

//SSD1306 constrast value
#define SSD1306_CONSTRAST_LOW 0x00
#define SSD1306_CONSTRAST_HIGH 0xFF

//SSD1306 oscillator value (value to be add)
#define SSD1306_OSCILLATOR_FRQ 0x80

//SSD1306 height value
#define SSD1306_DISPLAY_HEIGHT 0x3F //To check

//SSD1306 vram address selection
#define SSD1306_SET_COLUMN 0x21
#define SSD1306_SET_PAGE 0x22

/****************************************************************
*
* I2C function settings for SSD1306 ( use it only if you want these default settings )
*
****************************************************************/

//I2C init function
void I2C_init_for_SSD1306();

/****************************************************************
*
* SSD1306 structures and functions
*
****************************************************************/

/******************************SSD1306 structure & init/destroy ******************************/

typedef struct SSD1306{
    uint8_t addr, h, *screen_buffer;
}SSD1306;

SSD1306 SSD1306_init(uint8_t addr, uint8_t screen_height);
void SSD1306_destroy(SSD1306 *display);

/******************************SSD1306 basic functions******************************/

void SSD1306_send_command(SSD1306 *display, uint8_t command);
void SSD1306_send_data(SSD1306 *display, uint8_t data);

/******************************SSD1306 graphic functions******************************/

void SSD1306_draw_pixel(SSD1306 *display, uint8_t x, uint8_t y, uint8_t pixel_value);
void SSD1306_clean(SSD1306 *display, uint8_t pixel_value);
void SSD1306_blit_screen(SSD1306 *display);

/******************************SSD1306 private functions******************************/

void _SSD1306_set_page(SSD1306 *display, uint8_t page);
void _SSD1306_set_column(SSD1306 *display, uint8_t column);

uint8_t _SSD1306_get_page(SSD1306 *display, uint8_t y);

#endif

/*??????????????????????????????
??????????????????????????????
???????????????????? ?????????
?????????????????????????????
?????????????????????????????
?????????????????????????????*/