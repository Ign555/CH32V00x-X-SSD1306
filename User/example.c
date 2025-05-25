#include "debug.h"
#include "SSD1306.h"
#include "SSD1306_img.h"
#include "SSD1306_writer.h"

extern const SSD1306_FONT font_data[];
extern const SSD1306_IMG img1[];

int w=0;

int main(void){

    SSD1306 ssd;
    uint8_t i = 0;

    //Init 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();

    USART_Printf_Init(115200);

    //SSD1306 init
    I2C_init_for_SSD1306();
    ssd = SSD1306_init(0x3C, SSD1306_32_PX);
    SSD1306_clean(&ssd, 0);

    SSD1306_draw_pixel(&ssd, 1, 0, 0);
    SSD1306_set_constrast(&ssd, 0xB4);
    SSD1306_render_screen(&ssd);

    while(1){
        SSD1306_write(&ssd, font_data, "JULES EST GAY\0", 0, 0);
        //SSD1306_draw_image(&ssd, img1, 72, 0);
        SSD1306_fast_render_screen(&ssd);
        /*
        for(i = 0 ; i < 255 ; i++){
            SSD1306_set_constrast(&ssd, i);
            Delay_Ms(10);
        }
        for(uint8_t j = 254 ; j > 0 ; j--){
            SSD1306_set_constrast(&ssd, j);
            Delay_Ms(10);
        }
        SSD1306_clean(&ssd, 0);*/
        
    }

}