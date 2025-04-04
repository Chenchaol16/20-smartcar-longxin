#ifndef BRUSHLESS_H
#define BRUSHLESS_H

#include "zf_common_headfile.h"

class BrushlessMotor {
public:
    // 构造函数，传入PWM设备路径
    BrushlessMotor(const char* pwm_device);
    
    // 初始化电机
    void initialize();
    
    // 设置速度 (0-100)
    void setSpeed(uint8_t speed);
    
    // 停止电机
    void stop();
    
    // 获取当前占空比
    uint16_t getCurrentDuty() const;

private:
    const char* pwm_device_;
    struct pwm_info pwm_info_;
    uint16_t current_duty_;
    
    // 将速度百分比转换为PWM占空比
    uint16_t speedToDuty(uint8_t speed) const;
};

#endif // BRUSHLESS_H