/****************************************************************
*
*
* SSD1306 img loader for CH32V00X
* Created by Ign555
* Version : v1.2
* File Creation : 21/05/2025
*
*
****************************************************************/

#include "SSD1306_img.h"

/****************************************************************
*
* SSD1306 image loader functions
*
****************************************************************/

void SSD1306_draw_image(SSD1306 *display, const uint8_t *image, uint8_t x, uint8_t y){

    uint8_t width = image[IMG_W_INDEX];
    uint8_t height = image[IMG_H_INDEX];
    uint8_t nb_byte = image[IMG_BYTES_PER_LINE_INDEX];
    uint8_t byte, shift;

    //Save the image pixels into the screen buffer
    for(uint8_t i = 0; i < height; i++){

        for(uint8_t j = 0; j < width; j++){
            byte = ( j / 8 ) + i * nb_byte; //Select the right byte
            shift = j % 8; //Shift applied to select the right pixel in the byte
            SSD1306_draw_pixel(display, x + j, y + i, (image[byte + IMG_METADATA_OFFSET] >> shift) & 0x01);
        }
        
    }

}