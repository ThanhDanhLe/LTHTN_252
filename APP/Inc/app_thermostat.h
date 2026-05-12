/*
 * app_thermostat.h
 *
 *  Created on: May 7, 2026
 *      Author: ACER
 */

#ifndef INC_APP_THERMOSTAT_H_
#define INC_APP_THERMOSTAT_H_

#include <stdint.h>

typedef enum {
    STATE_NORMAL = 0,   // Display and control fan
    STATE_SETTING       // Set up temperature threshold
} Thermostat_State_t;

void APP_Thermostat_Init(void);
void APP_Thermostat_Run(void);

#endif /* INC_APP_THERMOSTAT_H_ */
