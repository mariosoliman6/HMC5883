/*
 * HMC5883.c
 *
 *  Created on: Sep 12, 2024
 *      Author: Mario Soliman
 */

#include "../../Drivers/Device Drivers/HMC5883/HMC5883.h"

#define HMC5883_SLA 0x1e

uint16_t X;
uint16_t Y;
uint16_t Z;

int16_t twos_complement_16bit_to_signed(int16_t raw_value) {
    // If the MSB (bit 15) is set, the value is negative
    if (raw_value & 0x8000) {
        // Convert from two's complement for negative values
        raw_value = raw_value - 0x10000;  // Subtract 2^16 (65536) to get the signed integer
    }

    return raw_value;
}

HMC5883_Stat_t HMC5883_Init(HMC5883_t *Compass) {

	//Default Configurations
	Compass->Config_A = (0b11110000); //1 bit must be high, 8 samples,(15Hz)Output Data Rate,Normal mode
	Compass->Config_B = (0b00100000);   //Gain =1090(LSB/Gauss), 4 Reserved bits
	Compass->Mode_Register = (0b00000000); //6 Reserved bits, Single Measure mood

	uint8_t OK = 0;

	Compass->TxBuffer[0] = 0;
	Compass->TxBuffer[1] = Compass->Config_A;
	Compass->TxBuffer[2] = Compass->Config_B;
	Compass->TxBuffer[3] = Compass->Mode_Register;

	//Sending Buffer of default configurations
	OK |= Compass->HMC5883_HWInterface_t.I2C_Write(HMC5883_SLA,
			Compass->TxBuffer, 4);

	//Acknowledgement check
	if (OK) {
		return (HMC5883_ERROR);

	}

	else {
		return (HMC5883_OK);
	}

}

HMC5883_Stat_t HMC5883_Set_Sample(HMC5883_t *Compass, HMC5883_Samples_t Samples) {

	Compass->NumbersOfSamples = Samples;

	uint8_t Mask = 0b11;

	Compass->Config_A &= ~(Mask << 5);
	Compass->Config_A |= (Compass->NumbersOfSamples << 5);

	Compass->TxBuffer[0] = 0;
	Compass->TxBuffer[1] = Compass->Config_A;
	uint8_t OK = 0;

	OK |= Compass->HMC5883_HWInterface_t.I2C_Write(HMC5883_SLA,
			Compass->TxBuffer, 2);

	//Acknowledgement check
	if (OK) {
		return (HMC5883_ERROR);

	}

	else {
		return (HMC5883_OK);
	}

}

HMC5883_Stat_t HMC5883_Set_Rate(HMC5883_t *Compass,
		HMC5883_Data_Output_Rate_t Rate) {

	Compass->DataOutputRate = Rate;

	uint8_t Mask = 0b111;

	Compass->Config_A &= ~(Mask << 2);
	Compass->Config_A |= (Compass->DataOutputRate << 2);

	Compass->TxBuffer[0] = 0;
	Compass->TxBuffer[1] = Compass->Config_A;
	uint8_t OK = 0;

	OK |= Compass->HMC5883_HWInterface_t.I2C_Write(HMC5883_SLA,
			Compass->TxBuffer, 2);

	//Acknowledgement check
	if (OK) {
		return (HMC5883_ERROR);

	}

	else {
		return (HMC5883_OK);
	}

}

HMC5883_Stat_t HMC5883_Set_MeasurteMode(HMC5883_t *Compass,
		HMC5883_Measurement_Mode_t Mode) {

	Compass->MeasurementMode = Mode;

	uint8_t Mask = 0b11;

	Compass->Config_A &= ~(Mask);
	Compass->Config_A |= (Compass->MeasurementMode);

	Compass->TxBuffer[0] = 0;
	Compass->TxBuffer[1] = Compass->Config_A;
	uint8_t OK = 0;

	OK |= Compass->HMC5883_HWInterface_t.I2C_Write(HMC5883_SLA,
			Compass->TxBuffer, 2);

	//Acknowledgement check
	if (OK) {
		return (HMC5883_ERROR);

	}

	else {
		return (HMC5883_OK);
	}

}

HMC5883_Stat_t HMC5883_Set_Gain(HMC5883_t *Compass, HMC5883_Gain_t Gain) {

	Compass->Gain = Gain;

	uint8_t Mask = 0b111;

	Compass->Config_B &= ~(Mask << 5);
	Compass->Config_B |= (Compass->Gain << 5);

	Compass->TxBuffer[0] = 1;
	Compass->TxBuffer[1] = Compass->Config_B;
	uint8_t OK = 0;

	OK |= Compass->HMC5883_HWInterface_t.I2C_Write(HMC5883_SLA,
			Compass->TxBuffer, 2);

	//Acknowledgement check
	if (OK) {
		return (HMC5883_ERROR);

	}

	else {
		return (HMC5883_OK);
	}
}

HMC5883_Stat_t HMC5883_Set_OperatingMode(HMC5883_t *Compass,
		HMC5883_Mode_t Mode) {

	Compass->Mode = Mode;

	uint8_t Mask = 0b11;

	Compass->Mode_Register &= ~(Mask);
	Compass->Mode_Register |= (Compass->Mode);

	Compass->TxBuffer[0] = 2;
	Compass->TxBuffer[1] = Compass->Mode_Register;
	uint8_t OK = 0;

	OK |= Compass->HMC5883_HWInterface_t.I2C_Write(HMC5883_SLA,
			Compass->TxBuffer, 2);

	//Acknowledgement check
	if (OK) {
		return (HMC5883_ERROR);

	}

	else {
		return (HMC5883_OK);
	}

}

HMC5883_Stat_t HMC5883_Get_Readings(HMC5883_t *Compass) {

	uint8_t OK = 0;

	Compass->TxBuffer[0] = 0;

	OK |= Compass->HMC5883_HWInterface_t.I2C_Write(HMC5883_SLA,
			Compass->TxBuffer, 1);

	OK |= Compass->HMC5883_HWInterface_t.I2C_Read(HMC5883_SLA,
			Compass->RxBuffer, 13);

	Compass->X_MSB_Register = Compass->RxBuffer[3];
	Compass->X_LSB_Register = Compass->RxBuffer[4];
	X = (Compass->X_MSB_Register << 8) | (Compass->X_LSB_Register);

	Compass->X_Output_Data = twos_complement_16bit_to_signed(X);


Compass->Y_MSB_Register = Compass->RxBuffer[5];
Compass->Y_LSB_Register = Compass->RxBuffer[6];
Y = (Compass->Y_MSB_Register << 8) | (Compass->Y_LSB_Register);

Compass->Y_Output_Data = twos_complement_16bit_to_signed(Y);

Compass->Z_MSB_Register = Compass->RxBuffer[7];
Compass->Z_LSB_Register = Compass->RxBuffer[8];
Z = (Compass->Z_MSB_Register << 8) | (Compass->Z_LSB_Register);

Compass->Z_Output_Data = twos_complement_16bit_to_signed(Z);

Compass->RDY = Compass->RxBuffer[9];

Compass->RDY = Compass->RxBuffer[9] >> 1;

if (OK) {
	return (HMC5883_ERROR);

}

else {
	return (HMC5883_OK);
}

}
