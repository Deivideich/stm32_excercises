/*
 * button.c

 *  Created on: May 9, 2026
 *      Author: deivideich
 */

#include "button.h"
#include "main.h"

static GPIO_PinState previous_state;
static button_event_t pending_event = BTN_EVENT_NONE;

void button_update(void){
	// read usr input
	GPIO_PinState current_state = HAL_GPIO_ReadPin(USR_BTN_GPIO_Port, USR_BTN_Pin);

	// compare previous state vs current state to determine if a transition happened
	if (previous_state != current_state){

		// Get if the button was pressed or released
		if (current_state == GPIO_PIN_SET){
			pending_event = BTN_EVENT_PRESSED;
		}
		else{
			pending_event = BTN_EVENT_RELEASED;
		}
	}


	// update current state
	previous_state = current_state;

};

button_event_t button_get_event(void){
	// This function returns the event that just happened, and resets the event to let it be determined
	//when a new change in state is registered
	button_event_t event_copy = pending_event;
	pending_event = BTN_EVENT_NONE;
	return event_copy;
}

void button_init(void){
	// Initialize previous_state as the current usr input to avoid state change false positives
	previous_state = HAL_GPIO_ReadPin(USR_BTN_GPIO_Port, USR_BTN_Pin);
	pending_event = BTN_EVENT_NONE;
}
