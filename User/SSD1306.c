/****************************************************************
*
*
* SSD1306 Driver for CH32V00X
* Created by Ign555
* Version : v1.2
* File Creation : 30/03/2025
*
*
****************************************************************/

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
    i2c.I2C_ClockSpeed = 400000; //Set communication frequency at 400 kHz
    i2c.I2C_DutyCycle = I2C_DutyCycle_16_9; //Set the sck signal duty cycle to 16:9
    i2c.I2C_Ack = I2C_Ack_Enable; //Enable Ack
    i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //Use the 7 bits address mode ( simple mode )

    I2C_Init(I2C1, &i2c); //Initialise I2C peripherical

    I2C_Cmd(I2C1, ENABLE); //Enable I2C1 peripherical

}

/****************************************************************
*
* Welcome to SSD1306 section
*
****************************************************************/

/******************************SSD1306 init & destroy functions******************************/

SSD1306 SSD1306_init(uint8_t addr, uint8_t screen_height){
    
    SSD1306 display;

    if(addr > 0x7F)while(1); //Check if the SSD1306 address is valid, if not -> infinite loop
    if(screen_height < 15)while(1); //Check if the SSD1306 is size, if not ->infinite loop

    //Alloc memory to screen buffer
    display.screen_buffer = (uint8_t *)malloc(sizeof(uint8_t) * SSD1306_COLUMNS * SSD1306_PAGES);

    //Set display attribute
    display.addr = addr;
    display.h = screen_height;

    SSD1306_send_command(&display, SSD1306_TURN_OFF_SCREEN);
    SSD1306_send_command(&display, SSD1306_SET_CLOCK_DIVIDE_RATIO);SSD1306_send_command(&display, SSD1306_MAX_OSCILLATOR_FRQ); //To add more values
    SSD1306_send_command(&display, SSD1306_SET_MULTIPLEX_RATIO);SSD1306_send_command(&display, screen_height-1); //Set screen height ( edit multiplex ratio )
    SSD1306_send_command(&display, SSD1306_SET_DISPLAY_OFFSET);SSD1306_send_command(&display, SSD1306_NO_OFFSET); //No offset
    SSD1306_send_command(&display, SSD1306_START_LINE_0); //Set start line at 0 
    SSD1306_send_command(&display, SSD1306_SET_ADDRESSING_MODE);SSD1306_send_command(&display, SSD1306_HORIZONTAL_ADDRESSING_MODE);
    SSD1306_send_command(&display, SSD1306_CHARGE_PUMP_SETTINGS);SSD1306_send_command(&display, SSD1306_ENABLE_CHARGE_PUMP);
    SSD1306_send_command(&display, SSD1306_SET_HARDWARE_CONFIGURATION);SSD1306_send_command(&display, (screen_height == SSD1306_32_PX) ? SSD1306_SEQUENTIAL_COM_PIN_CONFIGURATION : SSD1306_ALTERNATIVE_COM_PIN_CONFIGURATION); //SEQ FOR 32 and ALTERNATES FOR 64
    SSD1306_send_command(&display, SSD1306_SET_CONTRAST);SSD1306_send_command(&display, SSD1306_CONSTRAST_LOW); //Set min constrast
    SSD1306_send_command(&display, SSD1306_SET_PRELOAD_DURATION);SSD1306_send_command(&display, 0x11); //One display clock period for each preloading phase
    SSD1306_send_command(&display, SSD1306_ADJUST_VCOMH_REGULATOR_OUTPUT);SSD1306_send_command(&display, SSD1306_VCOMH_ADJUST_1); //The lowest vcomh 
    SSD1306_send_command(&display, SSD1306_DISPLAY_MODE_NORMAL);
    SSD1306_send_command(&display, SSD1306_SCROLLING_DISABLE);
    SSD1306_send_command(&display, SSD1306_TURN_ON_SCREEN);
    
    return display;

}

void SSD1306_destroy(SSD1306 *display){

    free(display->screen_buffer);

}

/******************************SSD1306 private functions******************************/

static void _SSD1306_set_page(SSD1306 *display, uint8_t page){

    SSD1306_send_command(display, SSD1306_SET_PAGE);
    SSD1306_send_command(display, page);
    SSD1306_send_command(display, SSD1306_PAGES/2-1);

}

static void _SSD1306_set_column(SSD1306 *display, uint8_t column){

    SSD1306_send_command(display, SSD1306_SET_COLUMN);
    SSD1306_send_command(display, column);
    SSD1306_send_command(display, SSD1306_COLUMNS-1);

}

static uint8_t _SSD1306_get_page(uint8_t y){

    return y/SSD1306_NOMBER_OF_PIXEL_IN_A_PAGE;

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

void SSD1306_send_data(SSD1306 *display, uint8_t data){

    while(I2C_GetITStatus(I2C1, I2C_FLAG_BUSY) != RESET); //Wait untill the line is not busy

    I2C_GenerateSTART(I2C1, ENABLE); //Generate a start
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //Wait untill the chip switch in master mode

    I2C_Send7bitAddress(I2C1, display->addr << 1, I2C_Direction_Transmitter); //Send the 7 bit address ( for sending data only )
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); //Wait untill the master transmitter mode is enable
    
    I2C_SendData(I2C1, SSD1306_DATA_FLAG); //Send a byte to tell the display that it's a data
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //Wait untill the bytes has been sent

    I2C_SendData(I2C1, data); //Send the data
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //Wait untill the bytes has been sent
    
    I2C_GenerateSTOP(I2C1, ENABLE); //Generate a stop 
    
}

/******************************SSD1306 graphic functions******************************/

void SSD1306_draw_pixel(SSD1306 *display, uint8_t x, uint8_t y, uint8_t pixel_value){

    if(y >= display->h || x >= SSD1306_COLUMNS)return; //Do not draw pixel if it include a buffer over

    if(pixel_value){
        display->screen_buffer[_SSD1306_get_page(y)*SSD1306_COLUMNS + x] |= 1 << (y % SSD1306_NOMBER_OF_PIXEL_IN_A_PAGE);
    }else{
        display->screen_buffer[_SSD1306_get_page(y)*SSD1306_COLUMNS + x] &= ~(1 << (y % SSD1306_NOMBER_OF_PIXEL_IN_A_PAGE));
    }

}

void SSD1306_clean(SSD1306 *display, uint8_t pixel_value){
    
    //Fill the screen buffer with bit 0 ( black ) or 1 ( display color )
    for(uint8_t i = 0; i < display->h / SSD1306_PAGES; i++){
        for(uint8_t j = 0; j < SSD1306_COLUMNS; j++){
            display->screen_buffer[i*SSD1306_COLUMNS + j] = (pixel_value) ? 0xFF : 0x00;
        }
    }
    
}

void SSD1306_set_constrast(SSD1306 *display, uint8_t contrast){

    SSD1306_send_command(display, SSD1306_SET_CONTRAST);
    SSD1306_send_command(display, contrast);

}

void SSD1306_render_screen(SSD1306 *display){

    //Fill the screen memory with the screen_buff array
    for(uint8_t i = 0; i < display->h / SSD1306_PAGES ; i++){
        for(uint8_t j = 0; j < SSD1306_COLUMNS; j++){
            _SSD1306_set_page(display, i); //Place the memory cursor on a "page", for more information, please look in datasheet
            _SSD1306_set_column(display, j); //Place the memory cursor on a "column", for more information, please look in datasheet
            SSD1306_send_data(display, display->screen_buffer[i*SSD1306_COLUMNS + j]);
        }
    }
    
}

void SSD1306_fast_render_screen(SSD1306 *display){

    _SSD1306_set_page(display, 0); //Place the memory cursor on page 0
    _SSD1306_set_column(display, 0); //Place the memory cursor on a column 0

    while(I2C_GetITStatus(I2C1, I2C_FLAG_BUSY) != RESET); //Wait untill the line is not busy

    I2C_GenerateSTART(I2C1, ENABLE); //Generate a start
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); //Wait untill the chip switch in master mode

    I2C_Send7bitAddress(I2C1, display->addr << 1, I2C_Direction_Transmitter); //Send the 7 bit address ( for sending data only )
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); //Wait untill the master transmitter mode is enable
    
    I2C_SendData(I2C1, SSD1306_DATA_FLAG); //Send a byte to tell the display that it's a data
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //Wait untill the bytes has been sent
    
    //Fill the screen memory with the screen_buff array
    for(uint8_t i = 0; i < display->h / SSD1306_PAGES ; i++){
        for(uint8_t j = 0; j < SSD1306_COLUMNS; j++){
            I2C_SendData(I2C1, display->screen_buffer[i*SSD1306_COLUMNS + j]); //Send the command
            while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //Wait untill the bytes has been sent
        }
    }

    I2C_GenerateSTOP(I2C1, ENABLE); //Generate a stop 
    
}

/*
                                                                                                    
                                                                                                    
                                                                       .                            
                                                .                          .                        
                .                                                                                   
                                  .                           .                                     
                                          .                                                      .  
                                                  .                     .                           
                            .                                .                                      
                 .                 .        .     .                                                 
                                                          .                             .           
                                                                                                    
                                                                                       .            
                                                                                              .     
                                  .                                                                 
                                                                               .                    
                                                                                                  . 
                                           .                                                        
                                                                                                    
                                     .                                             .                
                                           .                                                        
                   @@@@@@            =@@@@@@            @@@@@@*       .    @@@@@@                   
                   @@@@@@            =@@@@@@            @@@@@@*            @@@@@@                   
              .    @@@@@@            =@@@@@@            @@@@@@*            @@@@@@                   
                   @@@@@@            =@@@@@@            @@@@@@*            @@@@@@                   
                   @@@@@@            =@@@@@@            @@@@@@*    .       @@@@@@                   
                   @@@@@@            =@@@@@@            @@@@@@*            @@@@@@   .               
                   @@@@@@            =@@@@@@            @@@@@@*            @@@@@@                   
                   @@@@@@            =@@@@@@            @@@@@@*            @@@@@@                   
                   @@@@@@            =@@@@@@      .     @@@@@@*            @@@@@@    .              
                   @@@@@@            =@@@@@@            @@@@@@*            @@@@@@                   
                   @@@@@@        .   =@@@@@@            @@@@@@*            @@@@@@                   
                   @@@@@@            =@@@@@@            @@@@@@*            @@@@@@                   
                   @@@@@@            =@@@@@@            @@@@@@*            @@@@@@                   
  .                      @@@@@@@@@@@@*                        =@@@@@@@@@@@@                         
                         @@@@@@@@@@@@*                        =@@@@@@@@@@@@                 .       
                         @@@@@@@@@@@@*                        =@@@@@@@@@@@@                         
                         @@@@@@@@@@@@*                        =@@@@@@@@@@@@                         
      .............        .                                             .       .............      
      .............        .                                           .         .............      
      .............     . .                                      .               ..............     
      .............                  =@@@@@@    . @@@@@@      =@@@@@@            .............      
      .............                  =@@@@@@.     @@@@@@      =@@@@@@            .............      
      .............  .               =@@@@@@      @@@@@@      =@@@@@@            .............      
      .............                  =@@@@@@      @@@@@@      =@@@@@@            .............     .
       .                       .            @@@@@@      @@@@@@*                          .          
                                            @@@@@@      @@@@@@*                                     
                    .                       @@@@@@      @@@@@@*     .            .                  
                                                                                                    
                                                                                                    
                                           .           .         . .        .                       
                          .                                                                         
     .                                                                   .                          
                                                                         .      .                   
*/                                                                                                    

