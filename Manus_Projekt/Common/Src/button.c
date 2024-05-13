/*
 * button.c
 *
 *  Created on: Sep 29, 2023
 *      Author: Sander
 */

#include "button.h"
#include "gpio.h"

Button_State Btn_State = Button_Up;

Button_State Button_GetState(){
	return Btn_State;
}

void Button_Update(){
	int State = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);
	if ((Button_GetState()==Button_Up || Button_GetState()==Button_Rising) && !State){
		Btn_State=Button_Up;
	}
	else if (Button_GetState()==Button_Down && !State){
		Btn_State=Button_Rising;
	}
	else if (Button_GetState()==Button_Up && State){
			Btn_State=Button_Falling;
		}
	else if ((Button_GetState()==Button_Down || Button_GetState()==Button_Falling) && State){
			Btn_State=Button_Down;
		}
}

void ButtonUpdate(){
	int State = HAL_GPIO_ReadPin(G2_GPIO_Port, G2_Pin) && ReadButtonWithDebounce();
	if ((Button_GetState()==Button_Up || Button_GetState()==Button_Rising) && !State){
		Btn_State=Button_Up;
	}
	else if (Button_GetState()==Button_Down && !State){
		Btn_State=Button_Rising;
	}
	else if (Button_GetState()==Button_Up && State){
			Btn_State=Button_Falling;
		}
	else if ((Button_GetState()==Button_Down || Button_GetState()==Button_Falling) && State){
			Btn_State=Button_Down;
		}
}


/*
uint8_t ReadButtonWithDebounce(GPIO_PinState* result){
//	GPIO_PinState State = HAL_GPIO_ReadPin(G2_GPIO_Port, G2_Pin);
	if ((Button_GetState()==Button_Rising) && State==GPIO_PIN_SET)
		return 0;
	return 1;
//}*/


