#include "SSD1306.h"
/****************************************************************
*
* I2C Initialisation part
*
****************************************************************/
void I2C_init_for_SSD1306(){

    //Set Clock command for GPIO, AF and I2C peripherical 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE); 

    
    //GPIO Init 
    GPIO_InitTypeDef i2c_gpio = {0}; //A structure to initialise GPIO  
    i2c_gpio.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    i2c_gpio.GPIO_Mode = GPIO_Mode_AF_OD; // Set GPIO pin as Alternate Function and open-drain ( for I2C )
    i2c_gpio.GPIO_Speed = GPIO_Speed_30MHz; //Set clock signal frequency for the GPIOC peripherical
    
    GPIO_Init(GPIOC, &i2c_gpio); //Initialise GPIO peripherical

    //I2C Init
    I2C_InitTypeDef i2c = {0}; //A structure to initialise I2C
    i2c.I2C_Mode = I2C_Mode_I2C; 
    i2c.I2C_ClockSpeed = 100000; //Set communication frequency at 400 kHz
    i2c.I2C_DutyCycle = I2C_DutyCycle_16_9; //Set the sck signal duty cycle to 16:9
    i2c.I2C_Ack = I2C_Ack_Enable; //Enable Ack
    i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //Use the 7 bits address mode ( simple mode )

    I2C_Init(I2C1, &i2c); //Initialise I2C peripherical

    I2C_Cmd(I2C1, ENABLE); //Enable I2C1 peripherical

}
/****************************************************************
*
* Welcome to SSD1306 part
*
****************************************************************/
SSD1306 SSD1306_init(uint8_t addr){
    
    SSD1306 display;

    if(addr > 0x7F)while(1); //Check if the SSD1306 address is valid, if not -> infinite loop

    //Set display attribute
    display.addr = addr;

    SSD1306_send_command(&display, SSD1306_TURN_OFF_SCREEN);
    SSD1306_send_command(&display, SSD1306_SET_CLOCK_DIVIDE_RATIO);SSD1306_send_command(&display, SSD1306_OSCILLATOR_FRQ);
    SSD1306_send_command(&display, SSD1306_SET_MULTIPLEX_RATIO);SSD1306_send_command(&display, SSD1306_DISPLAY_HEIGHT_128);
    SSD1306_send_command(&display, SSD1306_SET_DISPLAY_OFFSET);SSD1306_send_command(&display, 0x00); //No offset
    SSD1306_send_command(&display, SSD1306_START_LINE_0); //Set start line at 0 
    SSD1306_send_command(&display, SSD1306_TURN_OFF_SCREEN);
    SSD1306_send_command(&display, SSD1306_TURN_OFF_SCREEN);
    
    return display;

}

/******************************SSD1306 basic functions******************************/

void SSD1306_send_command(SSD1306 *display, uint8_t command){

    while(I2C_GetITStatus(I2C1, I2C_FLAG_BUSY) != RESET); //Wait untill the line is not busy

    I2C_GenerateSTART(I2C1, ENABLE); //Generate a start
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //Wait untill the chip switch in master mode

    I2C_Send7bitAddress(I2C1, display->addr << 1, I2C_Direction_Transmitter); //Send the 7 bit address ( for sending data only )
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); //Wait untill the master transmitter mode is enable
    
    I2C_SendData(I2C1, SSD1306_COMMAND_FLAG); //Send a byte to tell the display that it's a command
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //Wait untill the bytes has been sent

    I2C_SendData(I2C1, command); //Send the command
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //Wait untill the bytes has been sent
    
    I2C_GenerateSTOP(I2C1, ENABLE); //Generate a stop 
    
}
