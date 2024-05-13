/*
 * button.h
 *
 *  Created on: Sep 29, 2023
 *      Author: Sander
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

typedef enum {
    Button_Up,
    Button_Rising,
    Button_Falling,
    Button_Down,
} Button_State;

Button_State Button_GetState();

void Button_Update();


#endif /* INC_BUTTON_H_ */
