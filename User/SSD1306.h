#include "ch32v00x_gpio.h"
#include "ch32v00x_i2c.h"

#ifndef __SSD1306_H__
#define __SSD1306_H__

/****************************************************************
*
* SSD1306 command value
*
****************************************************************/

#define SSD1306_COMMAND_FLAG 0x00

//SSD1306 display On/Off
#define SSD1306_TURN_OFF_SCREEN 0xAE
#define SSD1306_TURN_ON_SCREEN  0xAF

//SSD1306 charge pump On/Off
#define SSD1306_DISABLE_CHARGE_PUMP 0x10
#define SSD1306_ENABLE_CHARGE_PUMP 0x14

//SSD1306 set display start line
#define SSD1306_START_LINE_0 0x40

//SSD1306 display settings value
#define SSD1306_HORIZONTAL_ADDRESSING_MODE 0x20
#define SSD1306_CHARGE_PUMP_SETTINGS 0x8D
#define SSD1306_SET_MULTIPLEX_RATIO 0xA8
#define SSD1306_SET_DISPLAY_OFFSET 0xD3
#define SSD1306_SET_CLOCK_DIVIDE_RATIO 0xD5

//SSD1306 oscillator value (value to be add)
#define SSD1306_OSCILLATOR_FRQ 0x80

//SSD1306 height value
#define SSD1306_DISPLAY_HEIGHT_128 0x3F

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
    uint8_t addr;

}SSD1306;

SSD1306 SSD1306_init(uint8_t addr);

/******************************SSD1306 basic functions******************************/

void SSD1306_send_command(SSD1306 *display, uint8_t command);
#endif