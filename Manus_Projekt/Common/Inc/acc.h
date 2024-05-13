/*
 * acc.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Sander
 */

#ifndef INC_ACC_H_
#define INC_ACC_H_

#include <stdint.h>

typedef struct{
	uint16_t x;
	uint16_t y;
	uint16_t z;
} acc_data;

typedef struct{
	uint16_t x;
	uint16_t y;
} acc_data_xy;


uint8_t Acc_CanReadWHOAMI();
uint8_t Acc_Init();
uint8_t Acc_HasData();
void Acc_ReadXYZ(acc_data *xyz);
void Acc_ReadXY(acc_data_xy *xy);

#endif /* INC_ACC_H_ */
