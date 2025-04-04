#include "zf_device_imu_core.h"
#include "zf_driver_file.h"

uint8 imu_type = DEV_NO_FIND;


int16 imu_acc_x,  imu_acc_y,  imu_acc_z;
int16 imu_gyro_x, imu_gyro_y, imu_gyro_z;
int16 imu_mag_x,  imu_mag_y,  imu_mag_z;

// iio框架获取设备名
const char imu_name_path[] = 
{
	"/sys/bus/iio/devices/iio:device1/name"
};

// iio框架对应的文件路径
const char *imu_file_path[] = 
{
	"/sys/bus/iio/devices/iio:device1/in_accel_x_raw",
	"/sys/bus/iio/devices/iio:device1/in_accel_y_raw",
	"/sys/bus/iio/devices/iio:device1/in_accel_z_raw",

	"/sys/bus/iio/devices/iio:device1/in_anglvel_x_raw",
	"/sys/bus/iio/devices/iio:device1/in_anglvel_y_raw",
	"/sys/bus/iio/devices/iio:device1/in_anglvel_z_raw",

	"/sys/bus/iio/devices/iio:device1/in_magn_x_raw",
	"/sys/bus/iio/devices/iio:device1/in_magn_y_raw",
	"/sys/bus/iio/devices/iio:device1/in_magn_z_raw",
};


void imu_get_dev_info()
{
	char str[20] = {0};
	if (file_read_string(imu_name_path, str) < 0)
	{
		printf("imu init error\r\n");
		imu_type = DEV_NO_FIND;
		return ;
	}

	if(strcmp(str, "IMU660RA") == 0)
	{
		imu_type = DEV_IMU660RA;
	}
	else if(strcmp(str, "IMU660RB") == 0)
	{
		imu_type = DEV_IMU660RB;
	}
	else if(strcmp(str, "IMU963RA") == 0)
	{
		imu_type = DEV_IMU963RA;
	}
	else
	{
		imu_type = DEV_NO_FIND;
	}

}


int16 imu_get_raw(const char *path)
{
	char str[20] = {0};
	file_read_string(path, str);
	return atoi(str);
}


