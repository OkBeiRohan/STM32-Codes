/*
 * dma.h
 *
 *  Created on: Aug 3, 2023
 *      Author: WON1COB
 */

#ifndef DMA_H_
#define DMA_H_

void dma2_mem2mem_config(void);
void dma2_transfer_start(uint32_t, uint32_t, uint32_t);

#endif /* DMA_H_ */