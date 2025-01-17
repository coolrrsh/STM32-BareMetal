#include <string.h>
#include "stm32f401x.h"


void SPI2_GPIOInits(void)
{
	GPIO_Handle_t SPIPins;
	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode =5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed= GPIO_SPEED_FAST;
	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&SPIPins);
	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
        GPIO_Init(&SPIPins);
	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
        GPIO_Init(&SPIPins);
	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
        GPIO_Init(&SPIPins);


}


void SPI2_Inits(void)
{
	SPI_Handle_t SPI2handle;
	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig= SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode= SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed= SPI_SCLK_SPEED_DIV2;
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM= SPI_SSM_DI;// software slave management enable for NSS pin
	SPI_Init(&SPI2handle);
}

//void GPIO_ButtonInit(void)

void GPIO_ButtonInit(void){
GPIO_Handle_t GPIOBtn;
GPIOBtn.pGPIOx = GPIOA;
GPIOBtn.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_0;
GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed= GPIO_SPEED_FAST;
GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl=GPIO_NO_PUPD;
GPIO_PeriClockControl(GPIOA,ENABLE);
GPIO_Init(&GPIOBtn);
}

void delay(void){
for(uint32_t i=0;i<500000/2; i++);
}


void SPI_VerifyResponse(uint8_t ackbyte)
{
	if(ackbyte== 1)
	{
		//ack
		return 1;
	}
	return 0;
}



int main(void)
{

char user_data[]= "Hello world";
GPIO_ButtonInit();
SPI2_GPIOInits();
SPI2_Inits();

SPI_SSOEConfig(SPI2,ENABLE);


//	while(!GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_NO_0);
/*
 *      Enable SPI2 peripheral
*/
       //SPI_SSIConfig(SPI2,ENABLE); //NSS HIGH AVOIDS MODF=1 error
	SPI_PeripheralControl(SPI2,ENABLE);
	
        uint8_t data;
	uint8_t dataLen = strlen(user_data);
	SPI_ReceiveData(SPI2,&data,1);
	delay();
	if(data==65){
		do_main();
	}
	//first send length information
	//to send data
	//SPI_SendData(SPI2,(uint8_t*)user_data,strlen(user_data));
	//while(SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG));
	//SPI_PeripheralControl(SPI2,DISABLE);



return 0;
}
