/*
 * bsp_lcd.c
 *
 *  Created on: May 7, 2026
 *      Author: ACER
 */

#include "bsp_lcd.h"
#include "bsp_delay.h"

static void LCD_Pulse_Enable(void) {
    LL_GPIO_SetOutputPin(LCD_PORT, LCD_EN_PIN);
    BSP_Delay_us(2);
    LL_GPIO_ResetOutputPin(LCD_PORT, LCD_EN_PIN);
    BSP_Delay_us(50);
}

static void LCD_Write_Nibble(uint8_t nibble) {
    (nibble & 0x01) ? LL_GPIO_SetOutputPin(LCD_PORT, LCD_D4_PIN) : LL_GPIO_ResetOutputPin(LCD_PORT, LCD_D4_PIN);
    (nibble & 0x02) ? LL_GPIO_SetOutputPin(LCD_PORT, LCD_D5_PIN) : LL_GPIO_ResetOutputPin(LCD_PORT, LCD_D5_PIN);
    (nibble & 0x04) ? LL_GPIO_SetOutputPin(LCD_PORT, LCD_D6_PIN) : LL_GPIO_ResetOutputPin(LCD_PORT, LCD_D6_PIN);
    (nibble & 0x08) ? LL_GPIO_SetOutputPin(LCD_PORT, LCD_D7_PIN) : LL_GPIO_ResetOutputPin(LCD_PORT, LCD_D7_PIN);

    LCD_Pulse_Enable();
}

void BSP_LCD_SendCommand(uint8_t cmd) {
    LL_GPIO_ResetOutputPin(LCD_PORT, LCD_RS_PIN);
    LCD_Write_Nibble(cmd >> 4);
    LCD_Write_Nibble(cmd & 0x0F);
    if (cmd == 0x01 || cmd == 0x02) {
        BSP_Delay_ms(2);
    }
}

void BSP_LCD_SendData(uint8_t data) {
    LL_GPIO_SetOutputPin(LCD_PORT, LCD_RS_PIN);
    LCD_Write_Nibble(data >> 4);
    LCD_Write_Nibble(data & 0x0F);
}

void BSP_LCD_Init(void) {
    BSP_Delay_ms(50);

    LL_GPIO_ResetOutputPin(LCD_PORT, LCD_RS_PIN);

    LCD_Write_Nibble(0x03);
    BSP_Delay_ms(5);
    LCD_Write_Nibble(0x03);
    BSP_Delay_ms(1);
    LCD_Write_Nibble(0x03);
    BSP_Delay_ms(1);

    LCD_Write_Nibble(0x02);
    BSP_Delay_ms(1);

    BSP_LCD_SendCommand(0x28);
    BSP_LCD_SendCommand(0x0C);
    BSP_LCD_SendCommand(0x06);
    BSP_LCD_Clear();
}

void BSP_LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t address;
    if (row == 0) {
        address = 0x80 + col;
    } else {
        address = 0xC0 + col;
    }
    BSP_LCD_SendCommand(address);
}

void BSP_LCD_Print(char *str) {
    while (*str) {
        BSP_LCD_SendData((uint8_t)(*str));
        str++;
    }
}

void BSP_LCD_Clear(void) {
    BSP_LCD_SendCommand(0x01);
}
