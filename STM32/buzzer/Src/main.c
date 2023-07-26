/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Press button to trigger the buzzer
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

void await_button_press(uint32_t *, uint32_t *);
void trigger_buzzer(uint32_t *);

int main(void)
{
  /**
   * To use button (SW1) and buzzer, enable the clock for the General Purpose I/O (GPIO) port B (For button) and port C (For buzzer)
   */
  uint32_t *ptr_RCC_AHB1ENR = (uint32_t *)0x40023830;
  *ptr_RCC_AHB1ENR |= (1 << 1); // Set bit 1 (GPIOBEN)
  *ptr_RCC_AHB1ENR |= (1 << 2); // Set bit 2 (GPIOCEN)

  /**
   * SW1 is connected to pin PB7. Set the mode of the pin PB7 to input mode.
   * Base address of the GPIO Port B Mode Register (GPIOB) = 0x4002 0400
   * Offset address of the mode register = 0x00
   * Address = 0x4002 0000
   * For SW1, Pin PB7 have to be set to input mode
   * Input Mode = 00
   */
  uint32_t *ptr_GPIOB_MODER = (uint32_t *)0x40020400;
  *ptr_GPIOB_MODER &= ~(1 << 15); // Clear bit 15
  *ptr_GPIOB_MODER &= ~(1 << 14); // Clear bit 14

  /**
   * Set the mode of the pin PC9 to output mode.
   * Base address of the GPIO Port C Mode Register (GPIOC) = 0x4002 0800
   * Offset address of the mode register = 0x00
   * Address = 0x4002 0800
   * For buzzer, Pin PC6 have to be set to output mode. For that set GPIOC6 bit. (At 12th position)
   * Output Mode = 01
   */
  uint32_t *ptr_GPIOC_MODER = (uint32_t *)0x40020800;
  *ptr_GPIOC_MODER |= (1 << 18);  // Set bit 18
  *ptr_GPIOC_MODER &= ~(1 << 19); // Clear bit 19

  /**
   * Change the output bit through the port PC6 using the Output Data Register (ODR)
   * Base address of the GPIO port C = 0x4002 0800
   * Offset address of the mode register = 0x14
   * Address = 0x4002 0814
   * For turning the buzzer ON, reset the ODR6 bit. For turning it OFF, set the ODR6 bit
   */
  uint32_t *ptr_GPIOC_ODR = (uint32_t *)0x40020814;

  /**
   * Read the input bit through the port PB7 using the Input Data Register (IDR)
   * Base address of the GPIO port B = 0x4002 0400
   * Offset address of the mode register = 0x10
   * Address = 0x4002 0010
   * For reading the input bit, read the IDR7 bit. (At 7th position)
   */
  uint32_t *ptr_GPIOA_IDR = (uint32_t *)0x40020010;

  await_button_press(ptr_GPIOC_ODR, ptr_GPIOA_IDR);
}

void await_button_press(uint32_t *ptr_GPIOC_ODR, uint32_t *ptr_GPIOA_IDR)
{
  while (1)
  {
    /**
     * Check if button is pressed
     */
    if (*ptr_GPIOA_IDR & (1 << 15))
    {
      trigger_buzzer(ptr_GPIOC_ODR);
    }
  }
}

void trigger_buzzer(uint32_t *ptr_GPIOC_ODR)
{
  if (*ptr_GPIOC_ODR & ~(1 << 9))
  {
    *ptr_GPIOC_ODR &= ~(1 << 9);
  }
  else
  {
    *ptr_GPIOC_ODR |= (1 << 9);
  }
}