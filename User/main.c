#include "debug.h"
#include "SSD1306.h"

int main(void){

    SSD1306 ssd;

    //Init 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    
    //SSD1306 init
    I2C_init_for_SSD1306();
    ssd = SSD1306_init(0x3C, SSD1306_32_PX);
    SSD1306_clean(&ssd, 1);
    SSD1306_set_constrast(&ssd, 0xB4);
    SSD1306_render_screen(&ssd);

    while(1){
        for(uint8_t i = 0 ; i <= 255 ; i++){
            SSD1306_set_constrast(&ssd, i);
            Delay_Ms(100);
        }
    }

}