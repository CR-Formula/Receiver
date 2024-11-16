/************************************************
* @file    uart.h 
* @author  
* @date    9/2024
* 
* @brief   UART Function Prototypes
***********************************************/
#include "stm32f042x6.h"

void USART1_Init(); 
void USART1_Send(uint8_t data);
uint8_t USART1_Receive_Blocking();
uint8_t USART1_Receive_Polling();

