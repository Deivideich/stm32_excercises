/*
 * button.h
 *
 *  Created on: May 9, 2026
 *      Author: deivideich
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdint.h>
#include <stdbool.h>

#include "main.h"

typedef enum
{
    BTN_EVENT_NONE = 0U,
    BTN_EVENT_PRESSED,
    BTN_EVENT_RELEASED
} button_event_t;

void button_init(void);
void button_update(void);

button_event_t button_get_event(void);

#endif /* INC_BUTTON_H_ */
