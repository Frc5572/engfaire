#include "arduino_i2c.h"
#include "ports.h"
#include "gear.h"
#include <cmath>
#include <Timer.h>
#include "drivetrain.h"
#include "gear.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>


union {
	float Float;
	uint8_t Byte[4];
}Recieve_DataS;

union {
	float Float;
	uint8_t Byte[4];
}Recieve_DataR;

union {
	float Float;
	uint8_t Byte[4];
}Recieve_DataL;

union {
	int Int;
	uint8_t Byte[2];
}Receive_info_data1;

union {
	int Int;
	uint8_t Byte[2];
}Receive_info_data2;

static I2C *wire;

void arduino_i2c::init() {
	wire = new I2C(I2C::kMXP, ARDUINO_ID);
	arduino_i2c::Send_ST_Arduino();
}

void arduino_i2c::clear_i2c(){
	delete wire;
}

// Send a SH (Shoot) Signal to Arduino
void arduino_i2c::Send_SH_Arduino() {
	unsigned char transmit_data[ARDUINO_TRAN_DATA_SIZE];
	transmit_data[0] = 'S';
	transmit_data[1] = 'H';
	transmit_data[2] = 0;
	transmit_data[3] = 0;
	transmit_data[4] = 0;
	transmit_data[5] = 0;
	wire->WriteBulk(transmit_data, ARDUINO_TRAN_DATA_SIZE);
}

// Send a Stop Signal to Arduino
void arduino_i2c::Send_ST_Arduino() {
	unsigned char transmit_data[ARDUINO_TRAN_DATA_SIZE];
	transmit_data[0] = 'S';
	transmit_data[1] = 'T';
	transmit_data[2] = 0;
	transmit_data[3] = 0;
	transmit_data[4] = 0;
	transmit_data[5] = 0;
	wire->WriteBulk(transmit_data, ARDUINO_TRAN_DATA_SIZE);
}

void arduino_i2c::Send(char a, char b, uint8_t c,  uint8_t d, uint8_t e, uint8_t f) {
	unsigned char transmit_data[ARDUINO_TRAN_DATA_SIZE];
	transmit_data[0] = a;
	transmit_data[1] = b;
	transmit_data[2] = c;
	transmit_data[3] = d;
	transmit_data[4] = e;
	transmit_data[5] = f;
	wire->WriteBulk(transmit_data, ARDUINO_TRAN_DATA_SIZE);
}

void arduino_i2c::ReadI2C(char *a1, char *a2, float *DataS, float *DataR, float *DataL, int *info_data1, int *info_data2) {
	static uint8_t data[ARDUINO_REC_DATA_SIZE];
	for (unsigned i = 0; i < ARDUINO_REC_DATA_SIZE; i++)
		data[i] = 0;
	int val=wire->ReadOnly(ARDUINO_REC_DATA_SIZE, data);
	//std::cout<<val<<std::endl;
	for (int i = 0; i < 4; i++){
		Recieve_DataR.Byte[i] = data[i + 2];
		Recieve_DataL.Byte[i] = data[i + 6];
		Recieve_DataS.Byte[i] = data[i + 10];
	}

	Receive_info_data1.Byte[0] = data[14];
	Receive_info_data1.Byte[1] = data[15];
	Receive_info_data2.Byte[0] = data[16];
	Receive_info_data2.Byte[1] = data[17];

	*a1 = data[0];
	*a2 = data[1];
	*DataS = Recieve_DataS.Float;
	*DataR = Recieve_DataR.Float;
	*DataL = Recieve_DataL.Float;
	*info_data1 = Receive_info_data1.Int;
	*info_data2 = Receive_info_data2.Int;

}
