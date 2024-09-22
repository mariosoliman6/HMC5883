/*
 * HMC5883.h
 *
 *  Created on: Sep 12, 2024
 *      Author: Mario Soliman
 */

#ifndef DEVICE_DRIVERS_HMC5883_HMC5883_H_
#define DEVICE_DRIVERS_HMC5883_HMC5883_H_

#include "stm32f1xx.h"
#include <string.h>

typedef enum {
	HMC5883_OK, HMC5883_ERROR,
} HMC5883_Stat_t;

typedef enum {

	One_Sample, Two_Sample, Four_Sample, Eight_Sample,

} HMC5883_Samples_t;

/// @enum
/// @brief
/// determine how fast data is sampled
typedef enum {
	Rate_0_75HZ,
	Rate_1_5HZ,
	Rate_3HZ,
	Rate_7_5HZ,
	Rate_15HZ,
	Rate_30HZ,
	Rate_75HZ,

} HMC5883_Data_Output_Rate_t;

typedef enum {
	Gain_1370_LSBperGauss,    //Ranged from +ve to -ve 0.88Ga
	Gain_1090_LSBperGauss,    //Ranged from +ve to -ve 1.3Ga
	Gain_820_LSBperGauss,     //Ranged from +ve to -ve 1.9Ga
	Gain_660_LSBperGauss,     //Ranged from +ve to -ve 2.5Ga
	Gain_440_LSBperGauss,     //Ranged from +ve to -ve 4Ga
	Gain_390_LSBperGauss,     //Ranged from +ve to -ve 4.7Ga
	Gain_330_LSBperGauss,     //Ranged from +ve to -ve 5.6Ga
	Gain_230_LSBperGauss,     //Ranged from +ve to -ve 8.1Ga

} HMC5883_Gain_t;

typedef enum {
	Normal_Config, Postive_Bias_Config, Negative_Bias_Config,
} HMC5883_Measurement_Mode_t;

typedef enum {
	Contious_Measurment, Single_Measurment, Idle_Mode, //the peripheral is connected to the power but it don't take read until we do

} HMC5883_Mode_t;

typedef enum {
	READY, NREADY,
} HM5883_Ready_t;

typedef enum {
	LOCKED, NLOCKED,
} HM5883_Lock_t;

typedef struct {
	uint8_t Config_A;
	uint8_t NumbersOfSamples :2;
	uint8_t DataOutputRate :3;
	uint8_t MeasurementMode :2;

	uint8_t Config_B;
	uint8_t Gain :3;

	uint8_t Mode_Register;
	uint8_t Mode :2;

	int16_t X_Output_Data;
	int8_t X_MSB_Register;
	uint8_t X_LSB_Register;

	int16_t Y_Output_Data;
	int8_t Y_MSB_Register;
	uint8_t Y_LSB_Register;

	int16_t Z_Output_Data;
	int8_t Z_MSB_Register;
	uint8_t Z_LSB_Register;

	uint8_t Status_Regester;
	uint8_t RDY :1;
	uint8_t Lock :1;

	uint8_t Identifier_A_Register;
	uint8_t Identifier_B_Register;
	uint8_t Identifier_C_Register;

	uint8_t TxBuffer[4];
	uint8_t RxBuffer[14];

	struct {
		uint8_t (*I2C_Read)(uint8_t SlA, uint8_t *Data, uint8_t Len);
		uint8_t (*I2C_Write)(uint8_t SlA, uint8_t *Data, uint8_t Len);

	} HMC5883_HWInterface_t;

} HMC5883_t;

HMC5883_Stat_t HMC5883_Init(HMC5883_t *Compass);
HMC5883_Stat_t HMC5883_Set_Sample(HMC5883_t *Compass, HMC5883_Samples_t Samples);
HMC5883_Stat_t HMC5883_Set_Rate(HMC5883_t *Compass,
		HMC5883_Data_Output_Rate_t Rate);
HMC5883_Stat_t HMC5883_Set_MeasurteMode(HMC5883_t *Compass,
		HMC5883_Measurement_Mode_t Mode);
HMC5883_Stat_t HMC5883_Set_Gain(HMC5883_t *Compass, HMC5883_Gain_t Gain);
HMC5883_Stat_t HMC5883_Set_OperatingMode(HMC5883_t *Compass,
		HMC5883_Mode_t Mode);
HMC5883_Stat_t HMC5883_Get_Readings(HMC5883_t *Compass);

#endif /* DEVICE_DRIVERS_HMC5883_HMC5883_H_ */
