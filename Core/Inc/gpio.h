/************************************************
* @file    gpio.h 
* @author  APBashara
* @date    6/2024
* 
* @brief   GPIO Function Prototypes
***********************************************/

#include "stm32f042x6.h"

/* Structs and Enums --------------------------------------------------------*/
typedef enum {
    GPIO_OK,
    GPIO_ERROR,
} GPIO_Status;

/* Function Prototypes ------------------------------------------------------*/

/**
 * @brief Initialize GPIO Pins used in the Telem system
 * @note PA8 LoRa RST, PA9 LoRa INT
 * 
 */
void GPIO_Init();

/**
 * @brief Toggle a given GPIO pin on or off
 * 
 * @param GPIO [GPIO_TypeDef*] GPIO Port to use
 * @param pin [uint8_t] Pin to toggle
 */
void Toggle_Pin(GPIO_TypeDef* GPIO, uint8_t pin);

/**
 * @brief Set a given GPIO pin high (Set to 1)
 * 
 * @param GPIO [GPIO_TypeDef*] GPIO Port to use
 * @param pin [uint8_t] Pin to set high
 */
void Set_Pin(GPIO_TypeDef* GPIO, uint8_t pin);

/**
 * @brief Clear a given GPIO pin (Set to 0)
 * 
 * @param GPIO [GPIO_TypeDef*] GPIO Port to use
 * @param pin [uint8_t] Pin to set low
 */
void Clear_Pin(GPIO_TypeDef* GPIO, uint8_t pin);