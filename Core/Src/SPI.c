/************************************************
* @file    SPI.c 
* @author  AlexNiedanOlsen
* @date    10/2024
* 
* @brief   Basic SPI Driver
*************************************************/

#include "SPI.h"

void SPI1_Init() {
    RCC ->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC ->AHBENR |= RCC_APB2ENR_SPI1EN; //ENABLES CLOCK

    GPIOA ->MODER &= ~GPIO_MODER_MODER0 & ~GPIO_MODER_MODER1 & ~GPIO_MODER_MODER11 & ~GPIO_MODER_MODER12;
    GPIOA ->MODER |= (0x2 << GPIO_MODER_MODER4_Pos) | (0x2 << GPIO_MODER_MODER5_Pos) | (0x2 << GPIO_MODER_MODER6_Pos) | (0x2 << GPIO_MODER_MODER7_Pos);
    //Below sets gpio pins to alternative function 5
    //GPIOA ->AFR[1] &= ~GPIO_AFRH_AFSEL4 & ~GPIO_AFRH_AFSEL5 & ~GPIO_AFRH_AFSEL6 & ~GPIO_AFRH_AFSEL7;
    //GPIOA ->AFR[1] |= (0x0 << GPIO_AFRH_AFSEL4_Pos) | (0x0 << GPIO_AFRH_AFSEL5_Pos) | (0x0 << GPIO_AFRH_AFSEL6_Pos) | (0x0 << GPIO_AFRH_AFSEL7_Pos);
    GPIOA ->AFR[0] &= ~GPIO_AFRL_AFSEL1 & ~GPIO_AFRL_AFSEL0;
    GPIOA ->AFR[0] |= (0x0 << GPIO_AFRL_AFSEL1_Pos) | (0x0 << GPIO_AFRL_AFSEL0_Pos);



    SPI1 ->CR1 &= ~SPI_CR1_CRCEN;
    SPI1 ->CR1 &= ~SPI_CR1_RXONLY;
    SPI1 ->CR1 &= ~SPI_CR1_LSBFIRST;  
    SPI1 ->CR1 &= ~SPI_CR1_BR_Pos;
    SPI1 ->CR1 |= (0X7 << SPI_CR1_BR_Pos); //sets baud rate to fPCLK/256
    SPI1 ->CR1 |= SPI_CR1_MSTR; 
    SPI1 ->CR1 &= ~SPI_CR1_CPOL & ~SPI_CR1_CPHA; //sets to mode 0

    SPI1 ->CR2 |= SPI_CR2_FRXTH; //sets to 8 bit
    SPI1 ->CR2 &= ~SPI_CR2_DS;
    SPI1 ->CR2 |= (0X7 << SPI_CR2_DS_Pos); //sets data size to 8 bits
    SPI1 ->CR2 &= ~SPI_CR2_TXEIE;
    SPI1 ->CR2 &= ~SPI_CR2_RXNEIE;
    SPI1 ->CR2 &= ~SPI_CR2_ERRIE;
    SPI1 ->CR2 &= ~SPI_CR2_FRF;
    SPI1 ->CR2 &= ~SPI_CR2_NSSP;
    SPI1 ->CR2 &= ~SPI_CR2_TXDMAEN;
    SPI1 ->CR2 &= ~SPI_CR2_RXDMAEN;
    SPI1 ->CR2 |= SPI_CR2_SSOE;
    SPI1 ->CR1 |= SPI_CR1_SPE; //Put at end of intialization function
}

void SPI1_Transmit(uint8_t data) {
    while (!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = data;  
    while (!(SPI1->SR & SPI_SR_TXE)); 
    while (SPI1->SR & SPI_SR_BSY);

}

int SPI1_Recieve(){ 
    while (!(SPI1->SR & SPI_SR_RXNE));  
    return SPI1->DR; 
}
