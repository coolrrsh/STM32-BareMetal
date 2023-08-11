#include "stm32_startup.h"


uint32_t vectors[] __attribute__((section(".isr_vector")))={
STACK_START,
(uint32_t)Reset_Handler,
(uint32_t)NMI_Handler,		          
(uint32_t)HardFault_Handler,			
(uint32_t)MemManage_Handler,			       
(uint32_t)BusFault_Handler,			     
(uint32_t)UsageFault_Handler,		    
0,
0,
0,
0,
(uint32_t)SVC_Handler,		           
(uint32_t)DebugMon_Handler,	        
0,
(uint32_t)PendSV_Handler,     		        
(uint32_t)SysTick_Handler,		            
(uint32_t)WWDG_Handler,			            
(uint32_t)PVD_Handler,			            
(uint32_t)TAMP_STAMP_Handler,		         
(uint32_t)RTC_WKUP_Handler,		         
(uint32_t)FLASH_Handler,			             
(uint32_t)RCC_Handler,			             
(uint32_t)EXTI10_Handler, 		           
(uint32_t)EXTI11_Handler,			            
(uint32_t)EXTI12_Handler, 		         
(uint32_t)EXTI13_Handler, 		        
(uint32_t)EXTI14_Handler,  		        
(uint32_t)DMA1_Stream0_Handler,  	 
(uint32_t)DMA1_Stream1_Handler,  	         
(uint32_t)DMA1_Stream2_Handler,       
(uint32_t)DMA1_Stream3_Handler,     
(uint32_t)DMA1_Stream4_Handler, 	    
(uint32_t)DMA1_Stream5_Handler,   
(uint32_t)DMA1_Stream6_Handler,	    
(uint32_t)ADC_Handler,         	    
(uint32_t)EXTI9_5_Handler,    	    
(uint32_t)TIM1_BRK_TIM9_Handler,      
(uint32_t)TIM1_UP_TIM10_Handler,      
(uint32_t)TIM1_TRG_COM_TIM11_Handler, 
(uint32_t)TIM1CC_Handler,  	     
(uint32_t)TIM2_Handler,            
(uint32_t)TIM3_Handler,           
(uint32_t)TIM4_Handler,           
(uint32_t)I2C1_EV_Handler,         
(uint32_t)I2C1_ER_Handler,             
(uint32_t)I2C2_EV_Handler,    	    
(uint32_t)I2C2_ER_Handler,    	    
(uint32_t)SPI1_Handler,    	        
(uint32_t)SPI2_Handler,    	        
(uint32_t)USART1_Handler,    	        
(uint32_t)USART2_Handler,             
(uint32_t)EXTI15_10_Handler,        
(uint32_t)RTC_Alarm_Handler,         
(uint32_t)OTG_FS_WKUP_Handler,        
(uint32_t)DMA1_Stream7_Handler,       
(uint32_t)SDIO_Handler,        	    
(uint32_t)TIM5_Handler,          	    
(uint32_t)SPI3_Handler,    	        
(uint32_t)DMA2_Stream0_Handler,    
(uint32_t)DMA2_Stream1_Handler,    
(uint32_t)DMA2_Stream2_Handler,       
(uint32_t)DMA2_Stream3_Handler,       
(uint32_t)DMA2_Stream4_Handler,       
(uint32_t)OTG_FS_Handler,  	        
(uint32_t)DMA2_Stream5_Handler,    
(uint32_t)DMA2_Stream6_Handler,       
(uint32_t)DMA2_Stream7_Handler,       
(uint32_t)USART6_Handler,            
(uint32_t)I2C3_EV_Handler,           
(uint32_t)I2C3_ER_Handler,     	    
(uint32_t)FPU_Handler,              
(uint32_t)SPI4_Handler,             	
};

void Default_Handler(void)
{
    while(1);
}

void Reset_Handler(void){
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *pDst=(uint8_t*)&_sdata;
    uint8_t *pSrc=(uint8_t*)&_la_data; 

    for(uint32_t i=0;i<size;i++){
        *pDst++ = *pSrc++;
    }

    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t*)&_sbss;
    for(uint32_t i=0;i<size;i++){
        *pDst++ = 0;
    }

    main();
 //copy .data section to SRAM
 //Init the .bss section to zero in SRAM
 //call Init function of std library
 //call main   
}