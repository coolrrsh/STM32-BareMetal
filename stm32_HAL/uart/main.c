#include "stm32f4xx_hal.h"
#include <string.h>
#include "main.h"

void SystemClockConfig(void);
void UART2_Init(void);
void Error_handler(void);

UART_HandleTypeDef huart2;

char *user_data="the application is running\r\n";
uint8_t rcvd_data;
uint8_t data_buffer[100];
uint32_t count=0;
uint8_t reception_complete = 0;

uint8_t to_upper(uint8_t data){

	return (data - ('a' - 'A'));
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart2){
	if(rcvd_data == '\r'){
		reception_complete = 1;
		data_buffer[count++]= '\r';
		HAL_UART_Transmit(huart2, data_buffer,count,HAL_MAX_DELAY);
	}
	else{
		data_buffer[count++] = rcvd_data;
	}

}

int main(void){
	HAL_Init();
	SystemClockConfig();
	UART2_Init();
	uint16_t data_len = strlen(user_data);
	HAL_UART_Transmit(&huart2, (uint8_t*)user_data, data_len, HAL_MAX_DELAY);
	/*while(1){
	HAL_UART_Receive(&huart2, &rcvd_data, 1, HAL_MAX_DELAY);
	if(rcvd_data == '\r'){
		break;
	}
	else {
	data_buffer[count++]=to_upper(rcvd_data);
	}
	  }

	data_buffer[count++]='\r';
	HAL_UART_Transmit(&huart2, (uint8_t*)data_buffer, count, HAL_MAX_DELAY);
	*/
	while(reception_complete != 1){
		HAL_UART_Receive_IT(&huart2, &rcvd_data,1);
	}
	while(1);
}

void SystemClockConfig(void)
{

}

void UART2_Init(void){
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;

	if( HAL_UART_Init(&huart2) != HAL_OK){
		Error_handler();
	}
}

void Error_handler(void){
	while(1){

	}
}

