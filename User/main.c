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
    ssd = SSD1306_init(0x3C);
    SSD1306_clean(&ssd, 0);
    SSD1306_blit_screen(&ssd);

    while(1){

    }

}