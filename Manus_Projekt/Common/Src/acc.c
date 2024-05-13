/*
 * acc.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Sander
 */

#include "acc.h"
#include "spi.h"
#include "led.h"

#define READ_SLAVE_OPERATION 0x80
#define WRITE_SLAVE_OPERATION 0x00

#define WHOAMI 0x0F
#define CTRL1 0x20
#define CTRL5 0x24
#define DATA 0x28

#define WHOAMI_DEFAULT_VALUE 0x44
#define CTRL1_WANTED_VALUE 0b01000100
#define CTRL5_WANTED_VALUE 0b00000001

void CS_START(){
	HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_RESET); //CS
}

void CS_END(){
	HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_SET); //CS
}

uint8_t Acc_CanReadWHOAMI() {
    uint8_t pTxData[2] = {READ_SLAVE_OPERATION | WHOAMI, 0};
    uint8_t pRxData[2] = {0, 0};
    CS_START(); // Kasuta ja implementeeri, kui puudub riistvaraline CS
    if (HAL_SPI_TransmitReceive(&hspi4, pTxData, pRxData, 2, HAL_MAX_DELAY) != HAL_OK) {
        LED_Red_Write(1);
    }
    CS_END(); // Kasuta ja implementeeri, kui puudub riistvaraline CS
    return pRxData[1] == WHOAMI_DEFAULT_VALUE;
}

uint8_t Acc_Init(){
	// CTRL1
	uint8_t pTxData[2] = {WRITE_SLAVE_OPERATION | CTRL1, CTRL1_WANTED_VALUE};
	uint8_t pRxData[2] = {0, 0};
	CS_START();
	if (HAL_SPI_TransmitReceive(&hspi4, pTxData, pRxData, 2, HAL_MAX_DELAY) != HAL_OK) {
		LED_Red_Write(1);
	}
	CS_END();


	// CTRL3
	pTxData[0] = (WRITE_SLAVE_OPERATION | CTRL5);
	pTxData[1] = CTRL5_WANTED_VALUE;
	pRxData[0] = 0;
	pRxData[1] = 0;
	CS_START();
	if (HAL_SPI_TransmitReceive(&hspi4, pTxData, pRxData, 2, HAL_MAX_DELAY) != HAL_OK) {
		LED_Red_Write(1);
	}
	CS_END();


	// Kontroll
	uint8_t pTxData2[6] = {READ_SLAVE_OPERATION | CTRL1, 0, 0, 0, 0, 0};
	uint8_t pRxData2[6] = {0, 0, 0, 0, 0, 0};

	CS_START();
	if (HAL_SPI_TransmitReceive(&hspi4, pTxData2, pRxData2, 6, HAL_MAX_DELAY) != HAL_OK) {
		LED_Red_Write(1);
	}
	CS_END();
	return pRxData2[1] == CTRL1_WANTED_VALUE && pRxData2[5] == CTRL5_WANTED_VALUE;
}

uint8_t Acc_HasData(){
	return HAL_GPIO_ReadPin(ACC_IN2_GPIO_Port,ACC_IN2_Pin);
}

void Acc_ReadXYZ(acc_data *xyz){
	uint8_t pTxData[7] = {READ_SLAVE_OPERATION | DATA, 0, 0, 0, 0, 0, 0};
	uint8_t pRxData[7] = {0, 0, 0, 0, 0, 0, 0};
	CS_START();
	if (HAL_SPI_TransmitReceive(&hspi4, pTxData, pRxData, 7, HAL_MAX_DELAY) != HAL_OK) {
		LED_Red_Write(1);
	}
	CS_END();
	xyz->x = (pRxData[2] << 8) | pRxData[1];
	xyz->y = (pRxData[4] << 8) | pRxData[3];
	xyz->z = (pRxData[6] << 8) | pRxData[5];
}

void Acc_ReadXY(acc_data_xy *xy){
	uint8_t pTxData[5] = {READ_SLAVE_OPERATION | DATA, 0, 0, 0, 0};
	uint8_t pRxData[5] = {0, 0, 0, 0, 0};
	CS_START();
	if (HAL_SPI_TransmitReceive(&hspi4, pTxData, pRxData, 7, HAL_MAX_DELAY) != HAL_OK) {
		LED_Red_Write(1);
	}
	CS_END();
	xy->x = (pRxData[2] << 8) | pRxData[1];
	xy->y = (pRxData[4] << 8) | pRxData[3];
}




