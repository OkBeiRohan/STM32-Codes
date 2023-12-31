/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Direct Memory Access (DMA)
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
#include <dma.h>
#include <common.h>

#define size 4
#define no_bytes 6

uint32_t src[size] = {213, 324, 553}, dst[size];

void init(void);

int main(void)
{
    uint32_t i;

    init();
    lcd_print(0, 0, "DMA2 Transfer");

    dma2_transfer_start((uint32_t)src, (uint32_t)dst, no_bytes);
    lcd_print(0, 0, "Awaiting TCIF0");
    while (!(DMA2->LISR &= (1 << 5)))
        ; // Wait for TCIF0 to be set

    lcd_print(0, 0, "DMA:            ");
    lcd_print(0, 1, "DST:     SRC:   ");
    for (i = 0; i < size; i++)
    {
        lcd_print(4, 0, "Transferring");

        dma2_transfer_start(src[i], dst[i], no_bytes);
        DMA2->LIFCR |= DMA_LIFCR_CTCIF0;

        lcd_print(4, 0, "Transferred ");
        lcd_print_int(13, 1, src[i], 0);
        lcd_print_int(4, 1, dst[i], 0);

        delay(500);
    }

    while (1)
        ;
}

void init(void)
{
    lcd_init(BIT_4_MODE);

    dma2_mem2mem_config();
}
