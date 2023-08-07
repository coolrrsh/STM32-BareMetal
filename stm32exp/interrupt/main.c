#include "stm32f401x.h"
#include <string.h>

void delay(void)
{
        for(uint32_t i=0;i<500000/2;i++);
}

int main(void)
{
GPIO_Handle_t GpioLed,GpioBtn;
memset(&GpioLed,0,sizeof(GpioLed));
memset(&GpioBtn,0,sizeof(GpioBtn));
GpioLed.pGPIOx=GPIOB;
GpioLed.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_14;
GpioLed.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT;
GpioLed.GPIO_PinConfig.GPIO_PinSpeed=GPIO_SPEED_FAST;
GpioLed.GPIO_PinConfig.GPIO_PinOPType=GPIO_OP_TYPE_PP;
GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl= GPIO_NO_PUPD;
GPIO_PeriClockControl(GPIOB,ENABLE);
GPIO_Init(&GpioLed);

GpioBtn.pGPIOx=GPIOA;
GpioBtn.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_12;
GpioBtn.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_IT_FT;
GpioBtn.GPIO_PinConfig.GPIO_PinSpeed=GPIO_SPEED_FAST;
GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl= GPIO_PIN_PU;
GPIO_PeriClockControl(GPIOA,ENABLE);
GPIO_Init(&GpioBtn);

GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10,NVIC_IRQ_PRI15);
GPIO_IRQITConfig(IRQ_NO_EXTI15_10,ENABLE);


void EXTI15_10_IRQHandler(void){
	delay();
	GPIO_IRQHandling(GPIO_PIN_NO_12);
	GPIO_ToggleOutputPin(GPIOB,GPIO_PIN_NO_14);
}

while(1);
        
        }

