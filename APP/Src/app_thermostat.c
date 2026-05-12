/*
 * app_thermostat.c
 *
 *  Created on: May 7, 2026
 *      Author: ACER
 */

#include "app_thermostat.h"
#include "bsp_gpio.h"
#include "bsp_lcd.h"
#include "bsp_ds18b20.h"
#include "bsp_delay.h"
#include <stdio.h>

#define DEBUG_LED()	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
#define DEBUG_OFFLED()	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);

Thermostat_State_t current_state = STATE_NORMAL;

uint8_t set_temp = 25;
int8_t current_temp = 0;
uint8_t is_fan_on = 0;

uint32_t last_read_time = 0;
uint32_t last_blink_time = 0;
uint8_t  blink_flag = 0;

extern volatile uint32_t system_tick_ms;

static void Display_Normal_State(void) {
    char buffer[17];
    BSP_LCD_SetCursor(0, 0);
    sprintf(buffer, "Temp:%2d%cC Set:%2d", current_temp, 0xDF, set_temp);
    BSP_LCD_Print(buffer);

    BSP_LCD_SetCursor(1, 0);
    if (is_fan_on) {
        BSP_LCD_Print("Fan: ON  Cooling");
    } else {
        BSP_LCD_Print("Fan: OFF Standby");
    }
}

static void Display_Setting_State(void) {
    char buffer[17];
    BSP_LCD_SetCursor(0, 0);

    if (system_tick_ms - last_blink_time >= 100) {
        blink_flag = !blink_flag;
        last_blink_time = system_tick_ms;

        if (blink_flag) {
            sprintf(buffer, "Temp:%02d%cC Set:  ", current_temp, 0xDF);
        } else {
            sprintf(buffer, "Temp:%02d%cC Set:%02d", current_temp, 0xDF, set_temp);
        }
        BSP_LCD_Print(buffer);
    }

    BSP_LCD_SetCursor(1, 0);
    BSP_LCD_Print(" -- SET MODE -- ");
}

/*App Funcs*/
void APP_Thermostat_Init(void) {
    BSP_Delay_Init();
    BSP_LCD_Init();
    BSP_DS18B20_Init();
    BSP_Fan_Control(0);

    current_state = STATE_NORMAL;
    BSP_Delay_ms(101);
    current_temp = BSP_DS18B20_ReadTemp();
    Display_Normal_State();
}

void APP_Thermostat_Run(void) {
    if (BSP_Button_Read(BTN_SET)) {
        if (current_state == STATE_NORMAL) {
            current_state = STATE_SETTING;
            BSP_LCD_Clear();
            blink_flag = 0;
        }
        else if (current_state == STATE_SETTING) {
            current_state = STATE_NORMAL;
            BSP_LCD_Clear();
            Display_Normal_State();
        }
    }

    switch (current_state) {
        case STATE_NORMAL:

        	if (system_tick_ms - last_read_time >= 500) {
                last_read_time = system_tick_ms;
                current_temp = BSP_DS18B20_ReadTemp();

                if (current_temp > set_temp) {
                    is_fan_on = 1;
                    BSP_Fan_Control(1);
                } else if (current_temp <= set_temp) {
                    is_fan_on = 0;
                    BSP_Fan_Control(0);
                }

                Display_Normal_State();
            }
            break;

        case STATE_SETTING:
            if (BSP_Button_Read(BTN_UP)) {
                set_temp++;
                blink_flag = 0;
            }
            if (BSP_Button_Read(BTN_DOWN)) {
                set_temp--;
                blink_flag = 0;
            }
            Display_Setting_State();
            break;

        default:
            current_state = STATE_NORMAL;
            break;
    }
}
