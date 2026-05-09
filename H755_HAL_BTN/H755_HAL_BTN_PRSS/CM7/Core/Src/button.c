/*
 * button.c

 *  Created on: May 9, 2026
 *      Author: deivideich
 */

#include "button.h"
#include "main.h"

static GPIO_PinState previous_state;
static button_event_t pending_event = BTN_EVENT_NONE;
static button_event_t previous_event = BTN_EVENT_NONE;
static uint32_t min_wait_stable_stat = 100; //ms
static uint32_t min_total_time_for_stable_stat;

void button_update(void){
	// read usr input
	GPIO_PinState current_state = HAL_GPIO_ReadPin(USR_BTN_GPIO_Port, USR_BTN_Pin);

	// compare previous state vs current state to determine if a transition happened
	if (previous_state != current_state){
		// If there was a change in the state then reset the timer
		debounce_timer_reset();
	}
	// In case the state is the same as the previous one, keep track on time
	else{
		if(get_state_timer() >= min_wait_stable_stat){
			if (current_state == GPIO_PIN_SET){
				pending_event = BTN_EVENT_PRESSED;
			}
			else if (current_state == GPIO_PIN_RESET){
				pending_event = BTN_EVENT_RELEASED;
			}
		}
		// In case not enough time has happened in this state, assume the bounce check is happening
		else{
			pending_event = BTN_EVENT_BOUNCE_CHECK;
		}
	}


	// update current state
	previous_state = current_state;

};

button_event_t button_get_event(void){
	// This function returns the event that just happened, and resets the event to let it be determined
	//when a new change in state is registered
	button_event_t event_copy = pending_event;

	if(previous_event == pending_event){
		return BTN_EVENT_REPEATED;
	}

	previous_event = pending_event;

	pending_event = BTN_EVENT_NONE;
	return event_copy;
}

void button_init(void){
	// Initialize previous_state as the current usr input to avoid state change false positives
	previous_state = HAL_GPIO_ReadPin(USR_BTN_GPIO_Port, USR_BTN_Pin);
	pending_event = BTN_EVENT_NONE;
	debounce_timer_reset();
}

// In case a new event happens, and if the state changed before the stabilization timer happened, then
// reset the debounce timer to allow the new satte to be processed
void debounce_timer_reset(void){
	min_total_time_for_stable_stat = HAL_GetTick();
}

// Evaluate the current time ct - min_time. In case CR - MIN_TIME >= wait then the state is consdered stable
uint32_t get_state_timer(void){
	return HAL_GetTick() - min_total_time_for_stable_stat;
}
