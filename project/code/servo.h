#ifndef SERVO_H
#define SERVO_H

#include "zf_common_headfile.h"

// 舵机参数配置
#define SERVO_PWM_DEVICE   "/dev/zf_device_pwm_servo"
#define SERVO_LEFT_MAX     75
#define SERVO_RIGHT_MAX    105
#define SERVO_CENTER_ANGLE 90

// 前置声明结构体
typedef struct pwm_info pwm_info_t;

// 舵机控制结构体
typedef struct {
    pwm_info_t pwm_cfg;
    float current_angle;
} ServoController;

// 函数声明
void servo_init(ServoController *servo);
void servo_set_angle(ServoController *servo, float angle);
void servo_control_by_error(ServoController *servo, int error, int max_error);


#endif