#include "stm32f401x_spi.h"

void SPI_Init(SPI_Handle_t *pSPIHandle){
//Periperal clock enable
	SPI_PeriClockControl(pSPIHandle->pSPIx,ENABLE);

//first lets configure the SPI_CR1 register
//1.Configure device mode
	uint32_t tempreg=0;
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << 2;
//2.Configure bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD){
	tempreg &= ~(1<<15);
       	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD){
	tempreg |= (1<< 15);
	}

	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY){
	tempreg &= ~(1<<15); //BIDI mode should be cleared
	tempreg |= (1<<10);//RXONLY BIT MUST BE SET
}

//3. Configure the SPI serial clock speed (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;

//4. Configure teh DFF
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << 11;


//5. Configure the CPOL
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

//6. Configure the CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;
	pSPIHandle->pSPIx->CR1 = tempreg;
	}





//Peripheral clock ENABLE
//
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
if(EnorDi == ENABLE){
        if(pSPIx == SPI1){
                SPI1_PCLK_EN();
        }


         else if(pSPIx == SPI2){
                SPI2_PCLK_EN();
        }

         else if(pSPIx == SPI3){
                SPI3_PCLK_EN();
        }

}

if(EnorDi == DISABLE){
        if(pSPIx == SPI1){
                SPI1_PCLK_DI();
        }


         else if(pSPIx == SPI2){
                SPI2_PCLK_DI();
        }

         else if(pSPIx == SPI3){
                SPI3_PCLK_DI();
        }

}

}





void SPI_DeInit(SPI_RegDef_t *pSPIx){
}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx,uint32_t FlagName)
{
	if(pSPIx->SR & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}


//This is blocking call
void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer,uint32_t Len){
	while(Len > 0){
		//1. wait until TXE is set
	while(SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG)== FLAG_RESET);
	if(pSPIx->CR1 & ( 1<< SPI_CR1_DFF))
	{
		pSPIx->DR = *((uint16_t*)pTxBuffer);
		Len--;
		Len--;
		(uint16_t*)pTxBuffer++;
	}
	else{
		pSPIx->DR = *pTxBuffer;
		Len--;
		pTxBuffer++;
	}
	
}}




void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len){
 while(Len > 0){
                //1. wait until TXE is set
        while(SPI_GetFlagStatus(pSPIx,SPI_RXNE_FLAG)== FLAG_RESET);
        
	//2. check DFF bit it CR1
	if(pSPIx->CR1 & ( 1<< SPI_CR1_DFF))
        {
                *((uint16_t*)pRxBuffer)= pSPIx->DR;
                Len--;
                Len--;
                (uint16_t*)pRxBuffer++;
        }
        else{
                 *((uint16_t*)pRxBuffer)= pSPIx->DR;
                Len--;
                (uint16_t*)pRxBuffer++;
        }
}}

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
}

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
}

void SPI_IRQHandling(SPI_Handle_t *pHandle){
}

/*
 * Peripheral clock control
*/

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE){
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);

	}else{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}

}

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
        if(EnOrDi == ENABLE){
                pSPIx->CR1 |= (1 << SPI_CR1_SSI);

        }else{
                pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
        }

}

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
        if(EnOrDi == ENABLE){
                pSPIx->CR2 |= (1 << SPI_CR2_SSOE);

        }else{
                pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
        }

}


