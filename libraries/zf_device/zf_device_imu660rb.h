#ifndef _zf_device_imu660rb_h
#define _zf_device_imu660rb_h


#include "zf_common_typedef.h"

extern int16 imu660rb_acc_x, imu660rb_acc_y, imu660rb_acc_z;  
extern int16 imu660rb_gyro_x, imu660rb_gyro_y, imu660rb_gyro_z;

void imu660rb_get_acc(void);
void imu660rb_get_gyro(void);

#endif
