/*
 * bsp_delay.c
 *
 *  Created on: May 7, 2026
 *      Author: ACER
 */

#include "bsp_delay.h"
void BSP_Delay_Init(void) {
     LL_TIM_EnableCounter(TIM2);
}

void BSP_Delay_us(uint32_t us) {
    uint32_t start_tick = LL_TIM_GetCounter(TIM2);

    while ((LL_TIM_GetCounter(TIM2) - start_tick) < us) {
    }
}

void BSP_Delay_ms(uint32_t ms) {
    while (ms--) {
        BSP_Delay_us(1000);
    }
}
