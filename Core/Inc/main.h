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

/* System Defines -----------------------------------------------------------*/
#define LED_PIN                               (4)
#define LED_GPIO                              (GPIOA)
#define USB_BUF_LEN                           (128)

// LoRa Packet IDs
#define LORA_SUSPENSION_ID          (0x01) // 50 Hz
#define LORA_GPS_ID                 (0x02) // 25 Hz
#define LORA_ENGINE_ID              (0x03) // 20 Hz
#define LORA_BRAKES_ACCEL_ID        (0x04) // 10 Hz
#define LORA_TEMPERATURE_ID         (0x05) // 1 Hz

/* Data Structures  ---------------------------------------------------------*/
/**
 * @brief 50 Hz packet with ID 0x01
 * @note  Contains Front and Rear Suspension Potentiometer values
 */
typedef struct {

  uint16_t FrontPot;                // Front Right Suspension Damper
  uint16_t RearPot;                 // Rear Right Suspension Damper

} LoRa_Suspension_Packet;

/**
 * @brief 25 Hz packet with ID 0x02
 * @note  Contains GPS Latitude, Longitude, and Speed
 */
typedef struct {

  int32_t latGPS;                   // Latitude GPS
  int32_t longGPS;                  // Longitude GPS
  int32_t Speed;                    // Vehicle GPS Speed

} LoRa_GPS_Packet;

/**
 * @brief 20 Hz packet with ID 0x03
 * @note  Contains Engine RPM, Throttle Position, Steering Angle, and Brake Pressure
 */
typedef struct {

  uint16_t BrakePressure;           // Brake Pressure
  uint16_t ThrottleADC;             // Analog Throttle Position
  uint16_t Steering;                // Steering Angle
  uint16_t RPM;                     // Engine RPM
  uint16_t ThrottlePosSensor;       // Throttle Position from ECU
  uint16_t Lambda;                  // Lambda

} LoRa_Engine_Data_Packet;

/**
 * @brief 10 Hz packet with ID 0x04
 * @note  Contains Oil Pressure, Front and Rear Brake Temp, and Accelerometer values
 */
typedef struct {

  uint16_t OilPressure;             // Oil Pressure
  uint16_t FrontBrakeTemp;          // Front Right Brake Temp (F)
  uint16_t RearBrakeTemp;           // Rear Right Brake Temp (F)
  uint16_t AccelX;                  // Accelerometer X Axis
  uint16_t AccelZ;                  // Accelerometer Z Axis
  uint16_t AccelY;                  // Accelerometer Y Axis

} LoRa_Brakes_Accel_Packet;

/**
 * @brief 1 Hz packet with ID 0x05
 * @note  Contains Air and Coolant Temp
 */
typedef struct {

  uint16_t AirTemp;                 // Air Temp (F)
  uint16_t CoolTemp;                // Coolant Temp (F)

} LoRa_Temperature_Packet;

/**
 * @brief Telemetry Struct to hold all Telemetry Data
 * @note  Anything not in a LoRa packet should be in this struct
 */
typedef struct {
  // LoRa Packets
  LoRa_Suspension_Packet Suspension_Packet;           // 50 Hz
  LoRa_GPS_Packet GPS_Packet;                         // 25 Hz
  LoRa_Engine_Data_Packet Engine_Data_Packet;         // 20 Hz
  LoRa_Brakes_Accel_Packet Brakes_Accel_Packet;       // 10 Hz
  LoRa_Temperature_Packet Temperature_Packet;         // 1 Hz

} Telemetry;

/* Functions prototypes -----------------------------------------------------*/

/**
  * @brief Handles system errors.
  * 
  */
void Error_Handler(void);


#endif /* __MAIN_H */
