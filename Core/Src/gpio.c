/************************************************
* @file    gpio.c
* @author  APBashara
* @date    6/2024
* 
* @brief   Basic GPIO Driver
***********************************************/

#include "gpio.h"

void GPIO_Init() {
  // Enable GPIO Clock
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  SYSCFG->CFGR1 |= SYSCFG_CFGR1_PA11_PA12_RMP; // Remap PA11 and PA12 for USB

  // Configure USB and LED pins
  GPIOA->MODER &= ~GPIO_MODER_MODER4;
  GPIOA->MODER |= (1 << GPIO_MODER_MODER4_Pos);
  GPIOA->OTYPER &= ~GPIO_OTYPER_OT_4;
  GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR4;
  GPIOA->OSPEEDR |= (1 << GPIO_OSPEEDR_OSPEEDR4_Pos);
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR4;
}

/**
 * @brief Toggle a given GPIO pin on or off
 * 
 * @param GPIO [GPIO_TypeDef*] GPIO Port to use
 * @param pin [uint8_t] Pin to toggle
 */
void Toggle_Pin(GPIO_TypeDef* GPIO, uint8_t pin) {
  GPIO->ODR ^= (1 << pin);
}

/**
 * @brief Set a given GPIO pin high (Set to 1)
 * 
 * @param GPIO [GPIO_TypeDef*] GPIO Port to use
 * @param pin [uint8_t] Pin to set high
 */
void Set_Pin(GPIO_TypeDef* GPIO, uint8_t pin) {
  GPIO->BSRR |= (1 << pin);
}

/**
 * @brief Clear a given GPIO pin (Set to 0)
 * 
 * @param GPIO [GPIO_TypeDef*] GPIO Port to use
 * @param pin [uint8_t] Pin to set low
 */
void Clear_Pin(GPIO_TypeDef* GPIO, uint8_t pin) {
  GPIO->BSRR |= (1 << (pin+16));
}