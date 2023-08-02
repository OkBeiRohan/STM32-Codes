/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : USART communication
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
#include <common.h>

#define TIM_FREQ 16000000

void config_usart(void);
void usart_write(uint8_t);
uint8_t usart_read(void);

int main(void)
{
    uint8_t data = 0, counter;

    lcd_init(BIT_4_MODE);
    config_usart();
    lcd_print(0, 0, "USART: ");
    lcd_print(0, 1, "Received:");
    while (1)
    {
        for (counter = 0; counter < 0xFF; counter++)
        {
            usart_write(counter);
            data = usart_read();
            lcd_print(7, 0, "Received  ");
            lcd_print_int(10, 1, data, 1);
        }
    }
}

void config_usart(void)
{
    RCC->APB1ENR |= (1 << 18); // Enable USART3 clock
    RCC->AHB1ENR |= (1 << 2);  // Enable GPIOC clock

    set_alternate(GPIOC, 10); // Set PC10 to alternate function
    set_alternate(GPIOC, 11); // Set PC11 to alternate function

    // Set alternate function to USART2
    GPIOC->AFR[1] &= ~(0xF << 8);  // Clear AFRH8
    GPIOC->AFR[1] &= ~(0xF << 12); // Clear AFRH12
    GPIOC->AFR[1] |= (0x7 << 8);   // Set AFRH8 to AF7
    GPIOC->AFR[1] |= (0x7 << 12);  // Set AFRH12 to AF7

    // Set USART2 to 9600 baud, 8 data bits, 1 stop bit, no parity
    USART3->BRR = 0x0683;      // TIM_FREQ / 9600;
    USART3->CR1 |= (0xC << 0); // Enable receiver
    USART3->CR2 = 0;           // Enable transmitter
    USART3->CR3 = 0;           // No flow control
    USART3->CR1 |= (1 << 13);  // Enable USART2
}

void usart_write(uint8_t data)
{
    lcd_print(7, 0, "Awaiting    ");
    while (!(USART3->SR & (1 << 7)))
    {
    }
    lcd_print(7, 0, "Sending     ");
    USART3->DR = (data & 0xFF);
}

uint8_t usart_read(void)
{
    lcd_print(7, 0, "Awaiting    ");
    while (!(USART3->SR & (1 << 5)))
    {
    }
    lcd_print(7, 0, "Receiving   ");
    return USART3->DR;
}
