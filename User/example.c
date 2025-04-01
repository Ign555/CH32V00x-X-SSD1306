#include "debug.h"
#include "SSD1306.h"
void clearDisplay(SSD1306 *display) {
    for (uint8_t page = 0; page < 4; page++) { // 4 pages for 32 rows
        SSD1306_send_command(display, 0xB0 + page); // Set page address
        SSD1306_send_command(display, 0x00); // Lower column start address
        SSD1306_send_command(display, 0x10); // Upper column start address
        for (uint8_t col = 0; col < 128; col++) {
            SSD1306_send_data(display, 0x00);
        }
    }
}
int main(void){

    SSD1306 ssd;
    uint8_t i = 0;

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
    clearDisplay(&ssd);
    while(1){
        /*
        for(i = 0 ; i < 255 ; i++){
            SSD1306_set_constrast(&ssd, i);
            Delay_Ms(5);
        }
        for(uint8_t j = 254 ; j > 0 ; j--){
            SSD1306_set_constrast(&ssd, j);
            Delay_Ms(5);
        }
        */
    }

}