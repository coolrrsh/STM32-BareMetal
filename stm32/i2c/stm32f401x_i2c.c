#include "stm32f401x_i2c.h"


//Static function definitions
static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddr);
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

//
//
uint16_t AHB_PreScaler[8]={2,4,8,16,64,128,256,512};
uint8_t APB1_PreScaler[4]={2,4,8,16};
uint32_t RCC_GetPCLK1Value(void){

	uint32_t pclk1=0,SystemClk=0;
	uint32_t clksrc=0,temp=0,ahbp=0,apb1p=0;
	clksrc= ((RCC->CFGR >> 2) &0x3);
	
	if(clksrc==0){
		SystemClk= 16000000;
	}
	else if(clksrc==1){
		SystemClk= 8000000;
	}
	else if(clksrc==2){
	
	}
	
	// for AHB
	temp= ((RCC->CFGR >> 4)& 0xF);
	
	if(temp <8){
		ahbp =1;
	}

	else{
		ahbp=AHB_PreScaler[temp-8];
	}
	
	// for APB
	temp= ((RCC->CFGR >> 10)& 0x7);

        if(temp <4){
                apb1p =1;
        }

        else{
                apb1p=APB1_PreScaler[temp-4];
        }
	
	pclk1 = (SystemClk/ahbp)/apb1p ;
	return pclk1;

}


//Pre-requisites
void I2C_Init(I2C_Handle_t *pI2CHandle){
	
	
	uint32_t tempreg =0;
	
	//ack control bit
	tempreg |= (pI2CHandle->I2C_Config.I2C_ACKControl << 10);	
	pI2CHandle->pI2Cx->CR1= tempreg;

	//Configure the FREQ field of CR2
	tempreg=0;
	tempreg = RCC_GetPCLK1Value()/1000000U;
	pI2CHandle->pI2Cx->CR2 = (tempreg & 0x3F);
	
	//program the device own address
	tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress << 1;
	tempreg |= (1<<14);
	pI2CHandle->pI2Cx->OAR1 = tempreg;
	
	//CCR calculations
	uint16_t ccr_value=0;
	tempreg = 0;
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		//mode is standard mode
		ccr_value= (RCC_GetPCLK1Value()/ (2* pI2CHandle->I2C_Config.I2C_SCLSpeed));
		tempreg |= (ccr_value & 0xFFF);
	}
	else{
		//mode is fast mode
		tempreg |= (1<< 15);
		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14);
		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2){

			ccr_value = (RCC_GetPCLK1Value()/ (3 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
		}
		else{
			 ccr_value = (RCC_GetPCLK1Value()/ (25 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
		}
		tempreg |= (ccr_value & 0xFFF);

	}
	pI2CHandle->pI2Cx->CCR = tempreg;

}	



void I2C_DeInit(I2C_RegDef_t *pI2Cx);


//Interrupt handlling
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

//other Peripheral control Apis
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi){

if(EnOrDi == ENABLE){
	pI2Cx->CR1 |= (1 << I2C_CR1_PE);
}
else{
	pI2Cx->CR1 &= ~(1 << 0);
}

}


void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi){

if(EnorDi == ENABLE){
        if(pI2Cx == I2C1){
                I2C1_PCLK_EN();
        }


         else if(pI2Cx == I2C2){
                I2C2_PCLK_EN();
        }

         else if(pI2Cx == I2C3){
                I2C3_PCLK_EN();
        }

}

if(EnorDi == DISABLE){
        if(pI2Cx == I2C1){
                I2C1_PCLK_DI();
        }


         else if(pI2Cx == I2C2){
                I2C2_PCLK_DI();
        }

         else if(pI2Cx == I2C3){
                I2C3_PCLK_DI();
        }

}


}


static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddr){
	SlaveAddr = SlaveAddr << 1;
	SlaveAddr &= ~(1); //Salve address is slave address + r/w bit
	pI2Cx->DR = SlaveAddr;
}


static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx){
	uint32_t dummyRead = pI2Cx->SR1;
       	dummyRead = pI2Cx->SR2;
	(void)dummyRead;
}

	
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx){
	pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}



void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTxbuffer, uint32_t Len,uint8_t SlaveAddr){

	//Generate the START condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//Confirm that start generation is complete by checking the SB flag in SR1 register
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB));
	
	//Send the address of the slave with r/w bit set to w(0) (total 8 bits)
	I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx,SlaveAddr);

	//Confirms the address phase is completed by checing the ADDR flag in the SR1
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_ADDR));

	//Clear the ADDR flag according to its software sequence
	//Note: Until ADDR is cleared SCL will be stretched (pulled to LOW)
	I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

	//Send the data until len becomes 0
	while(Len>0)
	{
		while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_TXE));
		pI2CHandle->pI2Cx->DR = *pTxbuffer;
		pTxbuffer++;
		Len--;
	}

	//7. when len becomes zero wait for TXE=1 and BTF=1 before generating the stop condition
	//TXE=1, BTF=1, means that both SR and DR are empty and next transmission should begin
	//when BTF=1 SCL will be stretched (pulled to low)
	
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_TXE));

	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_BTF));


	//8. Generate STOP condition and master need not to wait for the completion of stop condition.
	//Note: generating STOP automatically clears the BTF
	I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

}


static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx){
	pI2Cx->CR1 |= (1 << I2C_CR1_START);
}



uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx,uint8_t FlagName){
if(pI2Cx->SR1 & FlagName){
	return FLAG_SET;
}
	return FLAG_RESET;
}




/*
 * Application callback
 */
void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv);

