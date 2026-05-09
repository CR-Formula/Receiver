/************************************************
* @file    main.c 
* @author  APBashara
* @date    5/2025
* 
* @brief   Main Code to run Tasks and Setup Peripherals
***********************************************/

/* Includes -----------------------------------------------------------------*/
#include "main.h"
#include "math.h"

/* Global Variables ---------------------------------------------------------*/
uint8_t packetRecv;
uint8_t LoRaPacketBuf[128];
uint8_t LoRaPacketLen;
uint8_t usbTxBuf[USB_BUF_LEN];
uint8_t usbBufLen;

/* Function Implementation --------------------------------------------------*/
int main(void) {
  HAL_Init(); // Used for USB
  SystemClock_Config(); // Sets to 48MHz using HSI48
  GPIO_Init();
  MX_USB_DEVICE_Init();

  float angle = 0;
  LoRa_GPS_Packet testPacket = {
    .ID = LORA_GPS_ID,
    .latGPS = 0,
    .longGPS = 0,
    .Speed = 0
  };

  while (1) {
    // Sample data
    angle += 0.1;
    testPacket.latGPS = (cos(angle) + 3 * sin(angle/5)) * 100000000;
    testPacket.longGPS = (sin(angle/3) + 3 * sin(angle/4)) * 100000000;
    
    HAL_Delay(100);
    Toggle_Pin(LED_GPIO, LED_PIN); // Toggle the LED pin
    CDC_Transmit_FS(&testPacket, sizeof(testPacket));
  }
}

void Error_Handler(void) {
  __disable_irq();
  while (1);
}
