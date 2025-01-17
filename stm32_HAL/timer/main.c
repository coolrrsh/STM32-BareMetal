#include <string.h>
#include "main.h"

void SystemClockConfig(void);
void Error_handler(void);
void TIMER3_Init(void);
void GPIO_Init(void);

TIM_HandleTypeDef htimer3;

int main(void){
	HAL_Init();
	SystemClockConfig();
	GPIO_Init();
	TIMER3_Init();
	HAL_TIM_Base_Start(&htimer3);
	//HAL_TIM_Base_Start_IT(&htimer3);

	while(1){

		while(!(TIM3->SR & TIM_SR_UIF));
		TIM3->SR =0;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}

	while(1);

	return 0;

}


void TIMER3_Init(void){
	htimer3.Instance = TIM3;
	htimer3.Init.Prescaler = 24;
	htimer3.Init.Period = 1600 -1;
	if(HAL_TIM_Base_Init(&htimer3) != HAL_OK){
		Error_handler();
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

void GPIO_Init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&ledgpio);

}

void SystemClockConfig(void){

}


void Error_handler(void){
        while(1){

        }
}


