#include "Driver_USART.h"

/* USART Driver */
extern ARM_DRIVER_USART Driver_USART3;

int main(){
    static ARM_DRIVER_USART * USARTdrv = &Driver_USART3;
  	USARTdrv->Initialize(NULL);   
	USARTdrv->PowerControl(ARM_POWER_FULL);  
	USARTdrv->Control(ARM_USART_MODE_ASYNCHRONOUS |
		ARM_USART_DATA_BITS_8 |
		ARM_USART_PARITY_NONE |                      
		ARM_USART_STOP_BITS_1 |                      
		ARM_USART_FLOW_CONTROL_NONE, 4800);  
	USARTdrv->Control (ARM_USART_CONTROL_TX, 1);    
	USARTdrv->Control (ARM_USART_CONTROL_RX, 1);     
	USARTdrv->Send("\nPress Enter to receive a message", 34);    

	return 0;
}