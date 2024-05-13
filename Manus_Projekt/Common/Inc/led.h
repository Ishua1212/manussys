/*
 * led.h
 *
 *  Created on: Sep 29, 2023
 *      Author: Sander
 */

#ifndef INC_LED_H_
#define INC_LED_H_


/*void LED_Green_Toggle();
void LED_Green_Write(GPIO_PinState);
GPIO_PinState LED_Green_Read();

void LED_Red_Toggle();
void LED_Red_Write(GPIO_PinState);
GPIO_PinState LED_Red_Read();*/


#define LED_Green_Toggle() HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin)
#define LED_Green_Write(GPIO_PinState) HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PinState)
#define LED_Green_Read() HAL_GPIO_ReadPin(LD3_GPIO_Port, LD3_Pin)

#define LED_Red_Toggle() HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin)
#define LED_Red_Write(GPIO_PinState) HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PinState)
#define LED_Red_Read() HAL_GPIO_ReadPin(LD4_GPIO_Port, LD4_Pin)


#endif /* INC_LED_H_ */
