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

/* Functions prototypes -----------------------------------------------------*/

/**
  * @brief Handles system errors.
  * 
  */
void Error_Handler(void);


#endif /* __MAIN_H */
