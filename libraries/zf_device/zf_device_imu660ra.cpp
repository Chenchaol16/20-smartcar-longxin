#include "zf_device_imu660ra.h"
#include "zf_device_imu_core.h"


int16 imu660ra_acc_x, imu660ra_acc_y, imu660ra_acc_z;
int16 imu660ra_gyro_x, imu660ra_gyro_y, imu660ra_gyro_z;



void imu660ra_get_acc(void)
{
	imu660ra_acc_x = imu_get_raw(imu_file_path[ACC_X_RAW]);
	imu660ra_acc_y = imu_get_raw(imu_file_path[ACC_Y_RAW]);
	imu660ra_acc_z = imu_get_raw(imu_file_path[ACC_Z_RAW]);
}

void imu660ra_get_gyro(void)
{
	imu660ra_gyro_x = imu_get_raw(imu_file_path[GYRO_X_RAW]);
	imu660ra_gyro_y = imu_get_raw(imu_file_path[GYRO_Y_RAW]);
	imu660ra_gyro_z = imu_get_raw(imu_file_path[GYRO_Z_RAW]);
}

