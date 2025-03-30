#include "debug.h"
#include "SSD1306.h"

int main(void){

    //Init 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    
    //GPIO Init
    GPIO_InitTypeDef gpreg = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_USART1 |RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    gpreg.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_5;
    gpreg.GPIO_Mode = GPIO_Mode_Out_PP;
    gpreg.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOC, &gpreg);

    //SSD1306 init
    I2C_init_for_SSD1306();
    SSD1306_init(0x3C);

    while(1){
        Delay_Ms(500);
        GPIO_WriteBit(GPIOC, GPIO_Pin_5, SET);
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, RESET);
        Delay_Ms(500);
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, SET);
        GPIO_WriteBit(GPIOC, GPIO_Pin_5, RESET);

    }

}