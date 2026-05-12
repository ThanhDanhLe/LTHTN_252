/*
 * bsp_delay.h
 *
 *  Created on: May 7, 2026
 *      Author: ACER
 */

#ifndef INC_BSP_DELAY_H_
#define INC_BSP_DELAY_H_
#include "stm32f4xx.h"
#include "stm32f4xx_ll_tim.h"
#include <stdint.h>

void BSP_Delay_Init(void);

void BSP_Delay_us(uint32_t us);

void BSP_Delay_ms(uint32_t ms);

#endif /* INC_BSP_DELAY_H_ */
