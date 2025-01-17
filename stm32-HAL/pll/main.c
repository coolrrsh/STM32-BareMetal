#define SYS_CLOCK_FREQ_50_MHZ 50

#define SYS_CLOCK_FREQ_84_MHZ 84

#define SYS_CLOCK_FREQ_120_MHZ 120

#define SYS_CLOCK_FREQ_180_MHZ 180

#include "stm32f4xx_hal.h"
#include <string.h>
#include "main.h"

void SystemClockConfig(void);
void UART2_Init(void);
void Error_handler(void);
void SystemClock_Config(uint8_t);

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

	//RCC_OscInitTypeDef osc_init;
	//RCC_ClkInitTypeDef clk_init;
    char msg[20];
	HAL_Init();

	SystemClock_Config(SYS_CLOCK_FREQ_50_MHZ);

	UART2_Init();

	        memset(msg,0,sizeof(msg));
	        sprintf(msg, "SYSCLK: %ld\r\n",HAL_RCC_GetSysClockFreq());
	        HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg), HAL_MAX_DELAY);

	        memset(msg,0,sizeof(msg));
	        sprintf(msg, "HCLK: %ld\r\n",HAL_RCC_GetHCLKFreq());
	        HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg), HAL_MAX_DELAY);

	        memset(msg,0,sizeof(msg));
	        sprintf(msg, "PCLK1: %ld\r\n",HAL_RCC_GetPCLK1Freq());
	        HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg), HAL_MAX_DELAY);

	        memset(msg,0,sizeof(msg));
	        sprintf(msg, "PCLK2: %ld\r\n",HAL_RCC_GetPCLK2Freq());
	        HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg), HAL_MAX_DELAY);



	while(1);

}

void SystemClock_Config(uint8_t clock_freq){
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;

	uint32_t FLatency = 0;

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osc_init.HSIState = RCC_HSI_ON;
	osc_init.HSICalibrationValue = 16;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;

	/*
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_BYPASS;
	//osc_init.HSICalibrationValue = 16;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	*/

	switch(clock_freq){
	case SYS_CLOCK_FREQ_50_MHZ:
	{
		osc_init.PLL.PLLM = 16;
		osc_init.PLL.PLLN = 100;
		osc_init.PLL.PLLP = 2;
		//osc_init.PLL.PLLQ = 2;

		clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
							 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
		clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
		clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
		FLatency = FLASH_ACR_LATENCY_1WS;
		break;
	}

	case SYS_CLOCK_FREQ_180_MHZ:
		{
			__HAL_RCC_PWR_CLK_ENABLE();

			__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
			__HAL_PWR_OVERDRIVE_ENABLE();

			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 360;
			osc_init.PLL.PLLP = 2;
			//osc_init.PLL.PLLQ = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
								 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
			FLatency = FLASH_ACR_LATENCY_5WS;
			break;
		}

	case SYS_CLOCK_FREQ_84_MHZ:
	{
		osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 168;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;


			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
										 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
					clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
					clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
					clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
					clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
					FLatency = FLASH_ACR_LATENCY_2WS;
			break;
	}
	case SYS_CLOCK_FREQ_120_MHZ:
	{
		    osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 240;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;


			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
										 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
					clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
					clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
					clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
					clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
					FLatency = FLASH_ACR_LATENCY_3WS;
			break;
	}
	default:
		return;
	}
	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK){
		Error_handler();
	}

	if(HAL_RCC_ClockConfig(&clk_init,FLatency) != HAL_OK){
			Error_handler();
	}

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
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

