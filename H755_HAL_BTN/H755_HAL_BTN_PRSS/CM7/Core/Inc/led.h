/*
 * led.h
 *
 *  Created on: May 10, 2026
 *      Author: deivideich
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"

typedef enum {
	LED_ON,
	LED_OFF
} LED_STATE ;

typedef enum {
	RED_LED,
	YELLOW_LED,
	GREEN_LED
} LED_COLOR;

void led_on(LED_COLOR color);
void led_off(LED_COLOR color);
void led_toggle(LED_COLOR color);

#endif /* INC_LED_H_ */
