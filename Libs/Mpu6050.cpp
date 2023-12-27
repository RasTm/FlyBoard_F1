#include "Mpu6050.hpp"

//Low Level Functions//
void Mpu6050_write(I2C_Base& object, uint8_t dev_reg, uint8_t transmit_data){
	object.write_byte(MPU6050_ADDR0, dev_reg, transmit_data);
}

void Mpu6050_read(I2C_Base& object, uint8_t dev_reg, uint8_t *receive_data){
	object.read_byte(MPU6050_ADDR0, dev_reg, receive_data);
}

void Mpu6050_multi_write(I2C_Base& object, uint8_t dev_reg, std::vector<uint8_t> &transmit_data){
	object.multi_byte_write(MPU6050_ADDR0, dev_reg, transmit_data);
}

void Mpu6050_multi_read(I2C_Base& object, uint8_t dev_reg, std::vector<uint8_t> &receive_data, uint8_t byte_count){
	object.multi_byte_read(MPU6050_ADDR0, dev_reg, receive_data, byte_count);
}

//Medium Level Functions//
void Mpu6050_config(I2C_Base& object, uint8_t accel_fs_select, uint8_t gyro_fs_select){
	object.write_byte(MPU6050_ADDR0, MPU6050_ACCEL_CONF, accel_fs_select);		//Mpu6050 Accel Set to 2g mode
	object.write_byte(MPU6050_ADDR0, MPU6050_GYRO_CONF,  gyro_fs_select);		//Mpu6050 Gyro  Set to 250 degre/sec
	object.write_byte(MPU6050_ADDR0, MPU6050_PWR_MGMT1, 0);						//Mpu6050 outoff the sleep mode
}

void Mpu6050_get_accel(I2C_Base& object, std::vector<int16_t> &accel_data){
	std::vector<uint8_t> pre_data;
	object.multi_byte_read(MPU6050_ADDR0, MPU6050_ACCEL_X_HOUT, pre_data, 6);
	accel_data[0] = ((pre_data[0]<<8) | pre_data[1]) / 16384;
	accel_data[1] = ((pre_data[2]<<8) | pre_data[3]) / 16384;
	accel_data[2] = ((pre_data[4]<<8) | pre_data[5]) / 16384;
	}

void Mpu6050_get_gyro(I2C_Base& object, std::vector<int16_t> &gyro_data){
	std::vector<uint8_t> pre_data;
	object.multi_byte_read(MPU6050_ADDR0, MPU6050_GYRO_X_HOUT, pre_data, 6);
	gyro_data[0] = ((pre_data[0]<<8) | pre_data[1]) / 131;
	gyro_data[1] = ((pre_data[2]<<8) | pre_data[3]) / 131;
	gyro_data[2] = ((pre_data[4]<<8) | pre_data[5]) / 131;
	}

void Mpu6050_get_temp(I2C_Base& object, int16_t *temp_data){
	std::vector<uint8_t> pre_data;
	object.multi_byte_read(MPU6050_ADDR0, MPU6050_TEMP_HOUT, pre_data, 2);
	*temp_data = ((pre_data[0]<<8) + pre_data[1]) / 340 + 37;
}
