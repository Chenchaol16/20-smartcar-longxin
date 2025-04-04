#ifndef _zf_device_imu963ra_h
#define _zf_device_imu963ra_h


#include "zf_common_typedef.h"

extern int16 imu963ra_acc_x, imu963ra_acc_y, imu963ra_acc_z;  
extern int16 imu963ra_gyro_x, imu963ra_gyro_y, imu963ra_gyro_z;
extern int16 imu963ra_mag_x, imu963ra_mag_y, imu963ra_mag_z;

void imu963ra_get_acc(void);
void imu963ra_get_gyro(void);
void imu963ra_get_mag(void);

#endif
