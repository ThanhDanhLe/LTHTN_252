#include "bsp_gpio.h"
#include "bsp_delay.h"


void BSP_Fan_Control(uint8_t state) {
    if (state) {
        LL_GPIO_ResetOutputPin(FAN_PORT, FAN_PIN);
    } else {
        LL_GPIO_SetOutputPin(FAN_PORT, FAN_PIN);
    }
}


uint8_t BSP_Button_Read(Button_ID_t btn_id) {
    uint32_t pin_mask;

    switch (btn_id) {
        case BTN_SET:
            pin_mask = BTN_SET_PIN;
            break;
        case BTN_UP:
            pin_mask = BTN_UP_PIN;
            break;
        case BTN_DOWN:
            pin_mask = BTN_DOWN_PIN;
            break;
        default:
            return 0;
    }

    if (LL_GPIO_IsInputPinSet(BTN_PORT, pin_mask) == 0) {
        BSP_Delay_ms(20);
        if (LL_GPIO_IsInputPinSet(BTN_PORT, pin_mask) == 0) {
            while (LL_GPIO_IsInputPinSet(BTN_PORT, pin_mask) == 0);
            return 1;
        }
    }

    return 0;
}
