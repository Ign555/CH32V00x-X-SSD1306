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

void SSD1306_write(SSD1306 *display, const SSD1306_FONT font[], char *text, uint8_t x, uint8_t y){

    if(font[0] > MAX_CHAR)while(1); //if the number of char is bigger than the ascii table

    //Draw it character by character
    for(uint8_t i = 0; text[i] != '\0'; i++){
        SSD1306_draw_char(display, font, text[i], x + font[FONT_W_INDEX] * i, y);
    }

}

void SSD1306_draw_char(SSD1306 *display, const SSD1306_FONT font[], char c, uint8_t x, uint8_t y){

    //Variables
    const uint8_t fw = font[FONT_W_INDEX]; //Store font width
    const uint8_t fh = font[FONT_H_INDEX]; //Store font height
    const uint8_t n_bytes_for_row = (font[FONT_W_INDEX] - 1) / 8 + 1; //Store the number of byte that take a character row
    
    uint8_t shift;
    uint8_t pixel;

    const int font_start_index = ( c - 48 ) * n_bytes_for_row * fh + FONT_METADATA_OFFSET; //Calculate the start point of the font array reading
    int byte;

    //Save the character's pixels into the screen buffer
    for(uint8_t i = 0; i < fh; i++){ //For each line

        for(uint8_t j = 0; j < fw ; j++){ //For each pixel in byte

            byte = font_start_index + i*n_bytes_for_row + j / 8; //Select the right byte
            shift = j % 8; //Shift applied to select the right pixel in the byte
            pixel = 0x01 << shift; //Mask to select the value of the pixel to write 

            SSD1306_draw_pixel(display, x + j, y + i, font[byte] & pixel);
            
            #ifdef __DEBUG__
                printf("start index : %d for %c line : %d col : b_%d p_%d\n", font_start_index, c, i, byte, j);
                printf("value : b_%x p_%kx\n", font[byte], ( font[byte] >> shift ) & 0x01);
            #endif

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



