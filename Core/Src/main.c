/************************************************
* @file    main.c 
* @author  APBashara
* @date    9/2024
* 
* @brief   Main Code to run the receiver
***********************************************/

#include "stm32f042x6.h"
#include "SPI.h"

void main() {
    SPI_Init();
    while(1) {
        SPI_Transmit('A');
    }
}