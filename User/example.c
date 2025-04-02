#include "debug.h"
#include "SSD1306.h"

int main(void){

    SSD1306 ssd;
    uint8_t i = 0;

    //Init 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    
    //SSD1306 init
    I2C_init_for_SSD1306();
    ssd = SSD1306_init(0x3C, SSD1306_64_PX);
    SSD1306_clean(&ssd, 0);
    for( i = 0; i < SSD1306_64_PX; i++){

        SSD1306_draw_pixel(&ssd, 0, i, 1);
    }
    SSD1306_set_constrast(&ssd, 0xB4);
    SSD1306_render_screen(&ssd);
    
    while(1){
        
        for(i = 0 ; i < 255 ; i++){
            SSD1306_set_constrast(&ssd, i);
            Delay_Ms(5);
        }
        for(uint8_t j = 254 ; j > 0 ; j--){
            SSD1306_set_constrast(&ssd, j);
            Delay_Ms(5);
        }
        
    }

}