/*
 * bsp_ds18b20.c
 *
 * Created on: May 7, 2026
 * Author: ACER
 */

#include "bsp_ds18b20.h"
#include "bsp_delay.h"

#define DS_PORT         GPIOA
#define DS_PIN          LL_GPIO_PIN_0

#define DS_OUT_LOW()    LL_GPIO_ResetOutputPin(DS_PORT, DS_PIN)
#define DS_READ()       LL_GPIO_IsInputPinSet(DS_PORT, DS_PIN)
#define DS_DIR_OUT()    LL_GPIO_SetPinMode(DS_PORT, DS_PIN, LL_GPIO_MODE_OUTPUT)	//pull bus low
#define DS_DIR_IN()     LL_GPIO_SetPinMode(DS_PORT, DS_PIN, LL_GPIO_MODE_INPUT)		//release bus
#define DEBUG_LED()		LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);

extern volatile uint32_t system_tick_ms;
static int8_t temp_int = 0;


static uint8_t DS18B20_Reset(void) {
    uint8_t presence = 0;
    DS_DIR_IN();
    BSP_Delay_us(5);
    DS_DIR_OUT();
    DS_OUT_LOW();
    BSP_Delay_us(480);
    DS_DIR_IN();
    BSP_Delay_us(70);

    if (DS_READ() == 0) {
        presence = 1;
        //DEBUG_LED();
    } else {
        presence = 0;
        //DEBUG_LED();
    }
    BSP_Delay_us(400);
    return presence;
}

static void DS18B20_WriteBit(uint8_t bit) {
    if (bit) {
        // bit 1: short bus low
    	DS_DIR_OUT();
    	DS_OUT_LOW();
        BSP_Delay_us(6);
        DS_DIR_IN();
        BSP_Delay_us(64);
    } else {
        // bit 0: long bus low
    	DS_DIR_OUT();
    	DS_OUT_LOW();
        BSP_Delay_us(60);
        DS_DIR_IN();
        BSP_Delay_us(10);
    }
}

static uint8_t DS18B20_ReadBit(void) {
    uint8_t bit = 0;

    DS_DIR_OUT();
    DS_OUT_LOW();       // Pull bus low to create read slot
    BSP_Delay_us(6);    // > 1us

    DS_DIR_IN();        // Release bus for sensor
    BSP_Delay_us(9);
    if (DS_READ()) {
        bit = 1;
    } else {
        bit = 0;
    }
    BSP_Delay_us(55);
    return bit;
}

static void DS18B20_WriteByte(uint8_t data) {
    for (uint8_t i = 0; i < 8; i++) {
        DS18B20_WriteBit(data & 0x01);
        data >>= 1;
    }
}

static uint8_t DS18B20_ReadByte(void) {
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++) {
        if (DS18B20_ReadBit()) {
            data |= (1 << i);
        }
    }
    return data;
}

static uint8_t DS18B20_CalcCRC8(uint8_t *data, uint8_t length) {
    uint8_t crc = 0U;
    for (uint8_t i = 0U; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0U; j < 8U; j++) {
            if (crc & 0x01U) {
                crc = (uint8_t)((crc >> 1U) ^ 0x8CU);
            } else {
                crc >>= 1U;
            }
        }
    }
    return crc;
}

void BSP_DS18B20_Init(void) {
    // Ensure release bus
    DS_DIR_IN();

    if (DS18B20_Reset()) {
        DS18B20_WriteByte(0xCC);  // Skip ROM
        DS18B20_WriteByte(0x4E);  // Write Scratchpad
        DS18B20_WriteByte(75);    // TH default
        DS18B20_WriteByte(70);    // TL default
        DS18B20_WriteByte(0x1F);  // Config: 9-bit resolution (Đo siêu tốc 94ms)
    }
    if (DS18B20_Reset()) {
        DS18B20_WriteByte(0xCC);  // Skip ROM
        DS18B20_WriteByte(0x44);  // Start convert temperature
    }
}


int8_t BSP_DS18B20_ReadTemp(void) {
	uint8_t scratchpad[9];
    int16_t temp_raw = 0;

    if (DS18B20_Reset()) {
        DS18B20_WriteByte(0xCC);    // Skip ROM
        DS18B20_WriteByte(0xBE); 	// Read Scratchpad

        for (uint8_t i = 0U; i < 9U; i++) {
            scratchpad[i] = DS18B20_ReadByte();
        }

        if (DS18B20_CalcCRC8(scratchpad, 8U) == scratchpad[8]) {
            temp_raw = (int16_t)(((uint16_t)scratchpad[1] << 8U) | scratchpad[0]);
            if (temp_raw >= 0) {
                temp_int = (int8_t)((temp_raw + 8) / 16);
            } else {
            	temp_int = (int8_t)((temp_raw - 8) / 16);
            }
        } else {
        	/*do nothing.*/
        }
    }

    if (DS18B20_Reset()) {
        DS18B20_WriteByte(0xCC);    // Skip ROM
        DS18B20_WriteByte(0x44);    // Convert T
    }

    return temp_int;
}
