/************************************************
* @file    main.c 
* @author  APBashara
* @date    5/2025
* 
* @brief   Main Code to run Tasks and Setup Peripherals
***********************************************/

/* Includes -----------------------------------------------------------------*/
#include "main.h"

/* Function Implementation --------------------------------------------------*/

int main(void) {

  SystemClock_Config(); // Sets to 48MHz using HSI48
  MX_USB_DEVICE_Init();

  while (1) {
    
  }
}

void Error_Handler(void) {
  __disable_irq();
  while (1);

}
