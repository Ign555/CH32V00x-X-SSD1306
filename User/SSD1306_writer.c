/****************************************************************
*
*
* SSD1306 writer for CH32V00X
* Created by Ign555
* Version : v1.2
* File Creation : 03/04/2025
*
*
****************************************************************/

#include "SSD1306_writer.h"

/****************************************************************
*
* SSD1306 writer functions
*
****************************************************************/

/******************************SSD1306 write functions******************************/

void SSD1306_write(SSD1306 *display, const SSD1306_FONT font[1028], char *text, uint8_t x, uint8_t y){

    if(font[0] > MAX_CHAR)while(1); //if the number of char is bigger than the ascii table
    
    //Draw it character by character
    for(uint8_t i = 0; text[i] != '\0'; i++){
        if(text[i] >= font[FONT_CHAR_NUMBER_INDEX]) continue; //Check if the character could exist in the table
        SSD1306_draw_char(display, font, text[i], x + font[FONT_W_INDEX] * i, y);
    }

}

void SSD1306_draw_char(SSD1306 *display, const SSD1306_FONT font[1028], char c, uint8_t x, uint8_t y){

    //Save the character's pixels into the screen buffer
    for(uint8_t i = 0; i < font[FONT_H_INDEX]; i++){
        for(uint8_t j = 0; j < font[FONT_W_INDEX]; j++){
            SSD1306_draw_pixel(display, x + j, y + i, ( font[c*font[FONT_H_INDEX] + i*(FONT_W_INDEX/BIT_IN_SSD1306_FONT + 1) + j/BIT_IN_SSD1306_FONT + FONT_METADATA_OFFSET] >> j )  & 0x01 );
        }
    }

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



