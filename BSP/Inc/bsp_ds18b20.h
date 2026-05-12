/*
 * bsp_ds18b20.h
 *
 *  Created on: May 7, 2026
 *      Author: ACER
 */

#ifndef INC_BSP_DS18B20_H_
#define INC_BSP_DS18B20_H_
#include "stm32f4xx_ll_gpio.h"
#include <stdint.h>

#define DS_PORT     GPIOA
#define DS_PIN      LL_GPIO_PIN_0

void BSP_DS18B20_Init(void);
int8_t BSP_DS18B20_ReadTemp(void);


#endif /* INC_BSP_DS18B20_H_ */
