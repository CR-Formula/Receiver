/************************************************
* @file    main.c 
* @author  APBashara
* @date    5/2025
* 
* @brief   Main Code to run Tasks and Setup Peripherals
***********************************************/

/* Includes -----------------------------------------------------------------*/
#include "main.h"

/* Global Variables ---------------------------------------------------------*/
uint8_t usbTxBuf[USB_BUF_LEN];
uint8_t usbBufLen;

/* Function Implementation --------------------------------------------------*/

int main(void) {
  HAL_Init(); // Initialize the HAL Library
  SystemClock_Config(); // Sets to 48MHz using HSI48
  GPIO_Init();
  MX_USB_DEVICE_Init();

  while (1) {
    usbBufLen = snprintf((char*)usbTxBuf, USB_BUF_LEN, "Test!\r\n");
    CDC_Transmit_FS(usbTxBuf, usbBufLen); // Transmit over USB CDC
    Toggle_Pin(LED_GPIO, LED_PIN); // Toggle the LED pin
  }
}

void Error_Handler(void) {
  __disable_irq();
  while (1);

}
