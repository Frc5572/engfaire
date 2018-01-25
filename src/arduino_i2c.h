#ifndef SRC_ARDUINO_I2C_H_
#define SRC_ARDUINO_I2C_H_
#include <I2C.h>


// I2C Communication definitions
#define ARDUINO_ID 8
#define ARDUINO_TRAN_DATA_SIZE 6
#define ARDUINO_REC_DATA_SIZE 18
#define ARDUINO_DEBUG false


namespace arduino_i2c{
	void ReadI2C(char *a1, char *a2, float *DataS, float *DataR, float *DataL, int *info_data1, int *info_data2);
	void Send_ST_Arduino();
	void Send_SH_Arduino();
	void init();
	void clear_i2c();
	void Send(char a, char b, uint8_t c, uint8_t d, uint8_t e, uint8_t f);
}

#endif /* SRC_ARDUINO_I2C_H_ */
