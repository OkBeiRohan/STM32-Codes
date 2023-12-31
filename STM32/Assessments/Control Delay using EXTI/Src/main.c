/**
******************************************************************************
* @file           : main.c
* @author         : Auto-generated by STM32CubeIDE
* @brief          : Main program body
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
#include <stm32f405xx.h>

void delay(uint32_t);
void init(void);

uint32_t count = 0;

int main(void)
{
  init();

  while (1)
  {
  }
}

void init()
{
  RCC->AHB1ENR |= (1 << 1);
  RCC->AHB1ENR |= (1 << 2);
  GPIOB->MODER &= ~(1 << 14);
  GPIOB->MODER &= ~(1 << 15);
  GPIOC->MODER |= (1 << 12);
  GPIOC->MODER &= ~(1 << 13);
  GPIOC->ODR |= (1 << 6);

  // Initialize EXTI for Button 1 (PB7)
  RCC->APB2ENR |= (1 << 14);
  SYSCFG->EXTICR[1] |= (1 << 12);
  EXTI->IMR |= (1 << 7);
  EXTI->RTSR |= (1 << 7);

  uint32_t *NVIC_ISER0 = (uint32_t *)0xE000E100;
  *NVIC_ISER0 |= (1 << 23);
}

void delay(uint32_t n)
{
  uint32_t i;
  for (i = 0; i < n * 16000; i++)
    ;
}

/**
 * Check for button interrupt
 *
 */
void EXTI9_5_IRQHandler(void)
{
  if (EXTI->PR & (1 << 7))
  {
    EXTI->PR |= (1 << 7);
    for (int i = 0; i < 6; i++)
    {
      GPIOC->ODR ^= (1 << 6);
      delay(3 + (count * 10));
    }

    count++;
    if (count == 4)
    {
      count = 0;
    }
  }
}
