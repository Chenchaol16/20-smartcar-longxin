#include "brushless.h"


// 构造函数
BrushlessMotor::BrushlessMotor(const char* pwm_device) 
    : pwm_device_(pwm_device), current_duty_(0) {
}

// 初始化电机
void BrushlessMotor::initialize() {
    pwm_get_dev_info(pwm_device_, &pwm_info_);
    printf("PWM freq = %d Hz, duty_max = %d\n", 
           pwm_info_.freq, pwm_info_.duty_max);
    stop(); // 初始化为停止状态
}

// 设置速度 (0-100)
void BrushlessMotor::setSpeed(uint8_t speed) {
    if (speed > 100) {
        speed = 100; // 限制最大速度为100%
    }
    current_duty_ = speedToDuty(speed);
    pwm_set_duty(pwm_device_, current_duty_);
}

// 停止电机
void BrushlessMotor::stop() {
    current_duty_ = speedToDuty(0);
    pwm_set_duty(pwm_device_, current_duty_);
}

// 获取当前占空比
uint16_t BrushlessMotor::getCurrentDuty() const {
    return current_duty_;
}

// 将速度百分比转换为PWM占空比
uint16_t BrushlessMotor::speedToDuty(uint8_t speed) const {
    // 映射速度0-100%到500-1000占空比
    return 500 + (speed * 5);
}