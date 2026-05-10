/*
 * led.c
 *
 *  Created on: May 10, 2026
 *      Author: deivideich
 */


#include "main.h"
#include "led.h"

void led_on(LED_COLOR color){
	if(color == RED_LED){
		HAL_GPIO_WritePin(RED_LED_GPIO_Port,RED_LED_Pin,GPIO_PIN_SET);
	}
	else if(color == GREEN_LED){
		HAL_GPIO_WritePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin,GPIO_PIN_SET);
	}
	else if(color == YELLOW_LED){
		HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port,YELLOW_LED_Pin,GPIO_PIN_SET);
	}
}

void led_off(LED_COLOR color){
	if(color == RED_LED){
		HAL_GPIO_WritePin(RED_LED_GPIO_Port,RED_LED_Pin,GPIO_PIN_RESET);
	}
	else if(color == GREEN_LED){
		HAL_GPIO_WritePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin,GPIO_PIN_RESET);
	}
	else if(color == YELLOW_LED){
		HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port,YELLOW_LED_Pin,GPIO_PIN_RESET);
	}
}

void led_toggle(LED_COLOR color){

	if(color == RED_LED){
		HAL_GPIO_TogglePin(RED_LED_GPIO_Port,RED_LED_Pin);
	}
	else if(color == GREEN_LED){
		HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port,GREEN_LED_Pin);
	}
	else if(color == YELLOW_LED){
		HAL_GPIO_TogglePin(YELLOW_LED_GPIO_Port,YELLOW_LED_Pin);
	}
}
