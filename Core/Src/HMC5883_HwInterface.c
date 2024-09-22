/*
 * HMC5883_HwInterface.c
 *
 *  Created on: Sep 12, 2024
 *      Author: Mario Soliman
 */

#include "HMC5883_HwInterface.h"

extern I2C_HandleTypeDef hi2c1;

uint8_t I2C_Write(uint8_t SlA, uint8_t *Data, uint8_t Len) {

	HAL_StatusTypeDef HAL_ERROR = HAL_I2C_Master_Transmit(&hi2c1, SlA << 1,
			Data, Len, 100);

	return (HAL_ERROR == HAL_OK ? 0 : 1);
}

uint8_t I2C_Read(uint8_t SlA, uint8_t *Data, uint8_t Len) {

	HAL_StatusTypeDef HAL_ERROR = HAL_I2C_Master_Receive(&hi2c1, SlA << 1, Data,
			Len, 100);

	return (HAL_ERROR == HAL_OK ? 0 : 1);
}
