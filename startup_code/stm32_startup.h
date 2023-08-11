#include<stdint.h>
#define SRAM_START  0x20000000
#define SRAM_SIZE   (64 * 1024) //64KB
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE))
#define STACK_START   SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);
void __libc_init_array(void);

void Reset_Handler(void);			  
void NMI_Handler			    (void) __attribute__ ((weak, alias("Default_Handler")));        
void HardFault_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));        
void MemManage_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));        
void BusFault_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));         
void UsageFault_Handler		    (void) __attribute__ ((weak, alias("Default_Handler")));   
void SVC_Handler		        (void) __attribute__ ((weak, alias("Default_Handler")));   
void DebugMon_Handler	        (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler     		(void) __attribute__ ((weak, alias("Default_Handler")));         
void SysTick_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));            
void WWDG_Handler				(void) __attribute__ ((weak, alias("Default_Handler")));            
void PVD_Handler				(void) __attribute__ ((weak, alias("Default_Handler")));            
void TAMP_STAMP_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));         
void RTC_WKUP_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));         
void FLASH_Handler			    (void) __attribute__ ((weak, alias("Default_Handler")));         
void RCC_Handler			    (void) __attribute__ ((weak, alias("Default_Handler")));         
void EXTI10_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI11_Handler				(void) __attribute__ ((weak, alias("Default_Handler")));            
void EXTI12_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void EXTI13_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));        
void EXTI14_Handler  			(void) __attribute__ ((weak, alias("Default_Handler")));        
void DMA1_Stream0_Handler  		(void) __attribute__ ((weak, alias("Default_Handler"))); 
void DMA1_Stream1_Handler  		(void) __attribute__ ((weak, alias("Default_Handler")));         
void DMA1_Stream2_Handler   	(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream3_Handler    	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void DMA1_Stream4_Handler 	    (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream5_Handler   	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream6_Handler	    (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC_Handler         	    (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI9_5_Handler    	    (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1CC_Handler  		    (void) __attribute__ ((weak, alias("Default_Handler")));     
void TIM2_Handler            	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_Handler           	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM4_Handler           	(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_Handler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_Handler    	    (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_Handler    	    (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_Handler    	        (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_Handler    	        (void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_Handler    	        (void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI15_10_Handler        	(void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_Alarm_Handler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_WKUP_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream7_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void SDIO_Handler        	    (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM5_Handler          	    (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_Handler    	        (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream0_Handler    	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream1_Handler    	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream2_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream3_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream4_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_Handler  	        (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream5_Handler    	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream6_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream7_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void USART6_Handler            	(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_Handler           	(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_ER_Handler     	    (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_Handler             	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void SPI4_Handler             	(void) __attribute__ ((weak, alias("Default_Handler"))); 