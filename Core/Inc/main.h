/************************************************
* @file    main.h 
* @author  APBashara
* @date    5/2025
* 
* @brief   Main Header File
***********************************************/

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes -----------------------------------------------------------------*/
#include "stm32f042x6.h"

#include "usb_device.h"

#include "sysclk.h"
#include "gpio.h"
#include <stdint.h>

/* System Defines -----------------------------------------------------------*/
#define LED_PIN                               (4)
#define LED_GPIO                              (GPIOA)
#define USB_BUF_LEN                           (128)

// #pragma pack(1) // Pack the structure to 1-byte alignment

// LoRa Packet IDs
#define LORA_GPS_ID                 (0x02) // 25 Hz
/**
 * @brief 25 Hz packet with ID 0x02
 * @note  Contains GPS Latitude, Longitude, and Speed
 */
typedef struct __attribute__((packed)) {
  const uint8_t ID;                 // Packet ID
  int32_t latGPS;                   // Latitude GPS
  int32_t longGPS;                  // Longitude GPS
  int8_t Speed;                     // Vehicle GPS Speed
} LoRa_GPS_Packet;


/* Functions prototypes -----------------------------------------------------*/

/**
  * @brief Handles system errors.
  * 
  */
void Error_Handler(void);


#endif /* __MAIN_H */
