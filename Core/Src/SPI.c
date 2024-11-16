/************************************************
* @file    SPI.c 
* @author  AlexNiedanOlsen
* @date    10/2024
* 
* @brief   Basic SPI Driver
*************************************************/

#include "SPI.h"

void SPI1_Init() {
    RCC ->AHB2ENR |= RCC_AHB2ENR_SPI1EN; //ENABLES CLOCK

    GPIOA ->MODER &= ~GPIO_MODER_MODER0 & ~GPIO_MODER_MODER1 &~GPOIO_MODER_MODER11 & ~GPIO_MODER_MODER12;
    GPIOA ->MODER |= (0x2 << GPIO_MODER_MODER0_Pos) | (0x2 << GPIO_MODER_MODER1_Pos) | (0x2 << GPIO_MODER_MODER11_Pos) | (0x2 << GPIO_MODER_MODER12_Pos);
    //Below sets gpio pins to alternative function 5
    GPIOA ->AFRH[1] &= ~GPIO_AFRH_AFSEL11 &~ GPIO_AFRH_AFSEL12;
    GPIOA ->AFRH[1] |= (0X5 << GPIO_AFRH_AFSEL11_Pos) | (0X5 << GPIO_AFRH_ASFSER12_Pos);
    GPIOA ->AFRL[0] &= ~GPIO_AFRL_AFSEL1 & ~GPIO_AFRL_AFSEL0;
    GPIOA ->AFRL[0] |= (0X5 << GPIO_AFRL_AFSEL1_Pos) | (0X5 << GPIO_AFRL_AFSEL0_Pos);


    SPI1 ->CR1 &= ~SPI1_CR1_CRCEN;
    SPI1 ->CR1 &= ~SPI1_CR1_RXONLY;
    SPI1 ->CR1 &= ~SPI1_CR1_LSBFIRST;  
    SPI1 ->CR1 &= ~SPI1_CR1_BR_Pos;
    SPI1 ->CR1 |= (0X7 << SPI1_CR1_BR_Pos); //sets baud rate to fPCLK/256
    SPI1 ->CR1 |= SPI1_CR1_MSTR; 
    SPI1 ->CR1 &= ~SPI1_CR1_CPOL & ~SPI1_CR1_CPHA; //sets to mode 0

    SPI1 ->CR2 &= ~SPI1_CR2_FRXTH; //sets to 16 bit data frame
    SPI1 ->CR2 &= ~SPI1_CR2_DS;
    SPI1 ->CR2 |= (0XF << SPI1_CR2_DS_Pos); //sets data size to 16 bits
    SPI1 ->CR2 &= ~SPI1_CR2_TXEIE;
    SPI1 ->CR2 &= ~SPI1_CR2_RXNEIE;
    SPI1 ->CR2 &= ~SPI1_CR2_ERRIE;
    SPI1 ->CR2 &= ~SPI1_CR2_FRF;
    SPI1 ->CR2 &= ~SPI1_CR2_NSSP;
    SPI1 ->CR2 &= ~SPI1_CR2_TXDMAEN;
    SPI1 ->CR2 &= ~SPI1_CR2_RXDMAEN;
    SPI1 ->CR2 |= SPI1_CR2_SSOE;
    SPI1 ->CR1 |= SPI1_CR1_SPE; //Put at end of intialization function
}

void SPI1_Transmit(uint8_t data) {


}

void SPI1_Recieve(){
    
}
