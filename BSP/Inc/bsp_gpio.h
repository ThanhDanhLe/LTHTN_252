#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include "stm32f4xx_ll_gpio.h"
#include <stdint.h>


#define BTN_PORT        GPIOB
#define BTN_SET_PIN     LL_GPIO_PIN_0
#define BTN_UP_PIN      LL_GPIO_PIN_1
#define BTN_DOWN_PIN    LL_GPIO_PIN_2

#define FAN_PORT        GPIOB
#define FAN_PIN         LL_GPIO_PIN_10

typedef enum {
    BTN_SET = 0,
    BTN_UP,
    BTN_DOWN
} Button_ID_t;

void BSP_Fan_Control(uint8_t state);
uint8_t BSP_Button_Read(Button_ID_t btn_id);

#endif /* BSP_GPIO_H */
