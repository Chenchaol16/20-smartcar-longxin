#include "zf_device_imu963ra.h"
#include "zf_device_imu_core.h"


int16 imu963ra_acc_x, imu963ra_acc_y, imu963ra_acc_z;
int16 imu963ra_gyro_x, imu963ra_gyro_y, imu963ra_gyro_z;
int16 imu963ra_mag_x, imu963ra_mag_y, imu963ra_mag_z;

void imu963ra_get_acc(void)
{
	imu963ra_acc_x = imu_get_raw(imu_file_path[ACC_X_RAW]);
	imu963ra_acc_y = imu_get_raw(imu_file_path[ACC_Y_RAW]);
	imu963ra_acc_z = imu_get_raw(imu_file_path[ACC_Z_RAW]);
}

void imu963ra_get_gyro(void)
{
	imu963ra_gyro_x = imu_get_raw(imu_file_path[GYRO_X_RAW]);
	imu963ra_gyro_y = imu_get_raw(imu_file_path[GYRO_Y_RAW]);
	imu963ra_gyro_z = imu_get_raw(imu_file_path[GYRO_Z_RAW]);
}

void imu963ra_get_mag(void)
{
	imu963ra_mag_x = imu_get_raw(imu_file_path[MAG_X_RAW]);
	imu963ra_mag_y = imu_get_raw(imu_file_path[MAG_Y_RAW]);
	imu963ra_mag_z = imu_get_raw(imu_file_path[MAG_Z_RAW]);
}