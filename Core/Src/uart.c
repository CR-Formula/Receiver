/************************************************
* @file    uart.c 
* @author  
* @date    9/2024
* 
* @brief   Basic UART Driver
***********************************************/

#include "uart.h"

void USART1_Init() {
    RCC ->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC ->AHBENR |= RCC_AHBENR_GPIOAEN;
    
    GPIOA ->MODER &= ~GPIO_MODER_MODER2 & ~GPIO_MODER_MODER10;
    GPIOA ->MODER |= (0x2 << GPIO_MODER_MODER10_Pos) | (0x2 << GPIO_MODER_MODER2_Pos);
    GPIOA ->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR2 & ~GPIO_OSPEEDR_OSPEEDR10;
    GPIOA ->OSPEEDR |= (0X3 << GPIO_OSPEEDR_OSPEEDR2_Pos) | (0x3 << GPIO_OSPEEDR_OPSPEEDR10_Pos);
    GPIOA ->OTYPER &= ~GPIO_OTYPER_OT_2 & ~GPIO_OTYPER_OT_10;
    GPIOA ->PUPDR &= ~GPIO_PUPDR_PUPDR2 & ~GPIO_PUPDR_PUPDR10;
    GPIOA ->AFR[0] |= (0x1 << GPIO_AFRL_AFRL2_Pos); 
    GPIOA ->AFR[1] |= (0x1 << GPIO_AFRH_AFRH10_Pos);

    USART1 ->CR1 &= ~USART_CR1_UE & ~USART_CR1_M;
    USART1 ->CR2 &= ~USART_CR2_STOP;
    USART1 ->CR1 &= ~USART_CR1_OVER8;
    USART1 ->BRR = 0x1A1;

    USART1 ->CR1 |= USART1_CR1_UE;
}

void USART1_Send(uint8_t data) {  
    USART1->CR1 |= USART_CR1_TE;
    USART1 ->TDR = data; 
    while(!USART1 ->ISR & USART_ISR_TC);
    }

uint8_t USART1_Receive_Blocking(){
    USART1 ->CR1 |= USART_CR1_RE;
    while(!USART1 ->ISR & USART_ISR_RXNE);
    return USART1 ->RDR;
}

uint8_t USART1_RECIEVE_POLLING(){
    USART1 ->CR1 |= USART_CR1_RE;
    if (USART1 ->ISR & USART_ISR_RXNE){
        return USART1 ->RDR;
    }
    else{
        return NULL;
    }
}