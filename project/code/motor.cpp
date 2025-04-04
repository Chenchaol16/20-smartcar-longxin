#include "motor.h"


// 静态成员初始化
MotorController::Motor MotorController::motor1(
    "/dev/zf_driver_gpio_motor_1", 
    "/dev/zf_device_pwm_motor_1");

MotorController::Motor MotorController::motor2(
    "/dev/zf_driver_gpio_motor_2", 
    "/dev/zf_device_pwm_motor_2");

uint8_t MotorController::max_speed_percent_ = 30;

// Motor 成员函数实现
MotorController::Motor::Motor(const char* dir_device, const char* pwm_device) 
    : dir_device_(dir_device), pwm_device_(pwm_device), current_duty_(0) {}

void MotorController::Motor::init() {
    pwm_get_dev_info(pwm_device_, &pwm_info_);
    gpio_set_level(dir_device_, 1);
    stop();
}

void MotorController::Motor::setSpeed(int8_t duty_percent) {
    if(duty_percent > static_cast<int8_t>(MotorController::max_speed_percent_)) {
        duty_percent = MotorController::max_speed_percent_;
    }
    if(duty_percent < -static_cast<int8_t>(MotorController::max_speed_percent_)) {
        duty_percent = -MotorController::max_speed_percent_;
    }
    
    if(duty_percent >= 0) {
        gpio_set_level(dir_device_, 1);
        pwm_set_duty(pwm_device_, duty_percent * (pwm_info_.duty_max / 100));
    } else {
        gpio_set_level(dir_device_, 0);
        pwm_set_duty(pwm_device_, -duty_percent * (pwm_info_.duty_max / 100));
    }
    
    current_duty_ = duty_percent;
}

void MotorController::Motor::stop() {
    pwm_set_duty(pwm_device_, 0);
    current_duty_ = 0;
}

int8_t MotorController::Motor::getCurrentSpeed() const {
    return current_duty_;
}

// MotorController 公共接口实现
void MotorController::setLeftMotor(int8_t speed) {
    motor1.setSpeed(speed);
}

void MotorController::setRightMotor(int8_t speed) {
    motor2.setSpeed(speed);
}

void MotorController::setMotors(int8_t leftSpeed, int8_t rightSpeed) {
    motor1.setSpeed(leftSpeed);
    motor2.setSpeed(rightSpeed);
}

void MotorController::stopAll() {
    motor1.stop();
    motor2.stop();
}

int8_t MotorController::getLeftSpeed() {
    return motor1.getCurrentSpeed();
}

int8_t MotorController::getRightSpeed() {
    return motor2.getCurrentSpeed();
}

void MotorController::setMaxSpeed(uint8_t percent) {
    if(percent > 100) percent = 100;
    max_speed_percent_ = percent;
}

// 原有MotorController成员函数实现
void MotorController::initialize() {
    motor1.init();
    motor2.init();
    atexit(cleanup);
    signal(SIGINT, sigintHandler);
}

void MotorController::cleanup() {
    printf("执行清理操作，停止所有电机\n");
    stopAll();
}

void MotorController::sigintHandler(int signum) {
    printf("收到Ctrl+C，程序即将退出\n");
    exit(0);
}

void MotorController::runTestSequence() {
    bool dir = true;
    int8_t duty = 0;
    
    while(true) {
        setMotors(duty, duty);
        
        if(dir) {
            duty++;
            if(duty >= static_cast<int8_t>(max_speed_percent_)) dir = false;
        } else {
            duty--;
            if(duty <= -static_cast<int8_t>(max_speed_percent_)) dir = true;
        }
        
        system_delay_ms(50);
    }
}