#include "stm32f4xx_hal.h"

void HAL_MspInit(void){

	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	SCB->SHCSR |= 0x7 << 16; //Enable the required system exceptions of arm cortex mx processor
	//3. configure the priority for the system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
	HAL_NVIC_SetPriority(UsageFault_IRQn,0,0);

}

void HAL_UART_MspInit(UART_HandleTypeDef *huart){
	GPIO_InitTypeDef gpio_uart;
	//1. enable clock for USART2 peripheral
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	//2. Do pin muxing
    gpio_uart.Pin = GPIO_PIN_2;
    gpio_uart.Mode = GPIO_MODE_AF_PP;
    gpio_uart.Pull = GPIO_PULLUP;
    gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
    gpio_uart.Alternate = GPIO_AF7_USART2; // UART2_TX
    HAL_GPIO_Init(GPIOA, &gpio_uart);
    gpio_uart.Pin = GPIO_PIN_3; //UART2_RX
    HAL_GPIO_Init(GPIOA, &gpio_uart);
	//3. Enable IRQ and set up the priority
    HAL_NVIC_EnableIRQ(USART2_IRQn);
    HAL_NVIC_SetPriority(USART2_IRQn,15,0);

}

