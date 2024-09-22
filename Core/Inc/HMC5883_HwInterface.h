/*
 * HMC5883_HwInterface.h
 *
 *  Created on: Sep 12, 2024
 *      Author: Mario Soliman
 */

#ifndef INC_HMC5883_HWINTERFACE_H_
#define INC_HMC5883_HWINTERFACE_H_


#include "stm32f1xx.h"

extern I2C_HandleTypeDef hi2c;

uint8_t I2C_Write(uint8_t SlA, uint8_t *Data, uint8_t Len);

uint8_t I2C_Read(uint8_t SlA, uint8_t *Data, uint8_t Len);


#endif /* INC_HMC5883_HWINTERFACE_H_ */
