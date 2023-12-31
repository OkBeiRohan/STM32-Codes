/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Rectangular Waveform using PWM
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
 * Write an Embedded C program to generate a rectangular waveform with different time periods for high and low using a DAC. Note: Generate 5 wave forms with one time period when change the waveform with another time period.
 */

#include <stdint.h>
#include <stm32f405xx.h>

#define LOW 0
#define HIGH 4095

void init(void);
void delay(uint32_t);
void loop(void);

int main(void)
{
	init();

	loop();
}

void init(void)
{
	RCC->AHB1ENR |= (1 << 0);  // Enable GPIOA clock
	GPIOA->MODER &= ~(3 << 8); // Clear PA4 mode bits
	GPIOA->MODER |= (3 << 8);  // Set PA4 to analog mode

	RCC->AHB1ENR |= (1 << 2);	// Enable GPIOC clock
	GPIOC->MODER &= ~(3 << 12); // Clear PC6 mode bits
	GPIOC->MODER |= (3 << 12);	// Set PC6 to analog mode

	RCC->APB1ENR |= (1 << 29); // Enable DAC clock
	DAC->CR |= (1 << 0);	   // Enable DAC channel 1
}

void loop()
{
	uint32_t time_period = 100, counter;
	while (1)
	{
		for (counter = 1; counter <= 5; counter++)
		{
			DAC->DHR12R1 = HIGH;
			delay(time_period);
			DAC->DHR12R1 = LOW;
			delay(time_period);
		}
		time_period += 500;
	}
}

void delay(uint32_t delay_ms)
{
	for (uint32_t i = 0; i < delay_ms * 4000; i++)
		;
}
