/*
 * bsp_lcd.h
 *
 *  Created on: May 7, 2026
 *      Author: ACER
 */

#ifndef INC_BSP_LCD_H_
#define INC_BSP_LCD_H_

#include "stm32f4xx_ll_gpio.h"
#include <stdint.h>

#define LCD_PORT        GPIOA
#define LCD_RS_PIN      LL_GPIO_PIN_4
#define LCD_EN_PIN      LL_GPIO_PIN_5
#define LCD_D4_PIN      LL_GPIO_PIN_6
#define LCD_D5_PIN      LL_GPIO_PIN_7
#define LCD_D6_PIN      LL_GPIO_PIN_8
#define LCD_D7_PIN      LL_GPIO_PIN_9

void BSP_LCD_Init(void);
void BSP_LCD_Clear(void);
void BSP_LCD_SetCursor(uint8_t row, uint8_t col);
void BSP_LCD_Print(char *str);

void BSP_LCD_SendCommand(uint8_t cmd);
void BSP_LCD_SendData(uint8_t data);

#endif /* INC_BSP_LCD_H_ */
