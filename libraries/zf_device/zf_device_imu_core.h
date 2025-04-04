#ifndef _zf_device_imu_core_h
#define _zf_device_imu_core_h


#include "zf_common_typedef.h"


enum imu_dev_enum
{
    DEV_NO_FIND  = 0x00,
    DEV_IMU660RA = 0x10,
    DEV_IMU660RB = 0x11,
    DEV_IMU963RA = 0x12,
};

enum path_index 
{
	ACC_X_RAW,
	ACC_Y_RAW,
	ACC_Z_RAW,
	
	GYRO_X_RAW,
	GYRO_Y_RAW,
	GYRO_Z_RAW,

	MAG_X_RAW,
	MAG_Y_RAW,
	MAG_Z_RAW,
};


extern int16 imu_acc_x,  imu_acc_y,  imu_acc_z;
extern int16 imu_gyro_x, imu_gyro_y, imu_gyro_z;
extern int16 imu_mag_x,  imu_mag_y,  imu_mag_z;

extern const char *imu_file_path[];
extern uint8 imu_type;


void imu_get_dev_info();
int16 imu_get_raw(const char *path);


#endif
