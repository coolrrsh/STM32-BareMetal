#include "stm32f401x_gpio.h"

void GPIO_Init(GPIO_Handle_t *pGPIOHandle){
uint32_t temp=0;
if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
 temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
 pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->MODER |= temp;

}

else{
//Handle Interrupts
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_IT_FT){
		//Configure FTST
		EXTI->FTSR |= (1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		//clear corresponding RSTR bit
		EXTI->RTSR &= ~(1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}
	else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_IT_RT){
		//Configure RTSR
		EXTI->RTSR |= (1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		//clear corresponding FTSR bit
		EXTI->FTSR &= ~(1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}
	else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_IT_RFT){
		//Configure RTSR
                EXTI->RTSR |= (1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
                //configure FTSR 
                EXTI->FTSR |= (1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

	}
	
	//2.Configure the GPIO port selection in SYSCFG_EXTICR
	uint8_t temp1=pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/4;
	
	uint8_t temp2=pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%4;
	
	uint8_t portcode= GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
	SYSCFG_PCLK_EN();
	SYSCFG->EXTICR[temp1]=portcode <<(temp2 *4);


	
	//3.Enable exti interrput delivery using IMR
	EXTI->IMR |= 1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;

}


//
temp=0;
temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
pGPIOHandle->pGPIOx->OSPEEDR |= temp;

temp=0;
temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
pGPIOHandle->pGPIOx->PUPDR |= temp;

temp=0;
temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
pGPIOHandle->pGPIOx->OTYPER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
pGPIOHandle->pGPIOx->OTYPER |= temp;

temp=0;

if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode== GPIO_MODE_ALTFN)
{
 	uint8_t temp1,temp2;
	temp1= (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber /8);
	temp2= (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber %8);
	pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4* temp2)); 
	pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4* temp2)); 
	
}



}


void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){

	if(pGPIOx == GPIOA){
                GPIOA_REG_RESET();
        }


         if(pGPIOx == GPIOB){
                GPIOB_REG_RESET();
        }

         if(pGPIOx == GPIOC){
                GPIOC_REG_RESET();
        }

}






/*peripheral clock init*/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,uint8_t EnorDi){

if(EnorDi == ENABLE){
	if(pGPIOx == GPIOA){
		GPIOA_PCLK_EN();
	}


	 else if(pGPIOx == GPIOB){
                GPIOB_PCLK_EN();
        }

	 else if(pGPIOx == GPIOC){
                GPIOC_PCLK_EN();
        }


}

else
{
	if(pGPIOx == GPIOA){
                GPIOA_PCLK_DI();
        }


         else if(pGPIOx == GPIOB){
                GPIOB_PCLK_DI();
        }

         else if(pGPIOx == GPIOC){
                GPIOC_PCLK_DI();
        }


}

}




uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber){

uint8_t value;
value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x1);
return value;
}


uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx){
uint16_t value;
value = (uint16_t)pGPIOx->IDR;
return value;
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t Value){

	if(Value==GPIO_PIN_SET){
	pGPIOx->ODR |= (1<<PinNumber);	
	}
	else{
	pGPIOx->ODR &= ~(1<< PinNumber);
	}

}

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint16_t Value){

	pGPIOx->ODR=Value;
}


void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber){
	pGPIOx->ODR ^= (1<<PinNumber);
}

void GPIO_IRQITConfig(uint8_t IRQNumber,uint8_t EnorDi){

	if(EnorDi == ENABLE)
	{
		if(IRQNumber <=31)
		{
			//program ISER0 register
			*NVIC_ISER0 |= (1<< IRQNumber);

		}

		 else if(IRQNumber >= 31 && IRQNumber < 64)
                {
                        //program ISER1 register 32 - 64
			*NVIC_ISER1 |= (1<< (IRQNumber%32));
                }


		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			//program ISER2 register 64 - 95
			*NVIC_ISER3 |= (1<< (IRQNumber % 64));
		}
	}

	else{
		 if(IRQNumber <=31)
                {
                        //program ISER0 register
			*NVIC_ICER0 |= (1<< IRQNumber);

                }

                 else if(IRQNumber >= 31 && IRQNumber < 64)
                {
                        //program ISER1 register 32 - 64
			*NVIC_ICER1 |= (1<< IRQNumber);
                }


                else if(IRQNumber >= 64 && IRQNumber < 96)
                {
                        //program ISER2 register 64 - 95
			*NVIC_ICER3 |= (1<< IRQNumber);
                }


	}
		



}


void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
{
uint8_t iprx = IRQNumber/4;
uint8_t iprx_section = IRQNumber %4;

uint8_t shift_amount = (8* iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << (8 * shift_amount));

}




void GPIO_IRQHandling(uint8_t PinNumber){
	
if(EXTI->PR & (1<< PinNumber))
{
EXTI->PR |= (1<< PinNumber);
}


}


