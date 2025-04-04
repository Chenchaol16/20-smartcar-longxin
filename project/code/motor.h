#ifndef MOTOR_H
#define MOTOR_H

#include "zf_common_headfile.h"
#include <cstdint>

/**
 * @brief 电机控制器类，提供对双电机的统一控制接口
 * 
 * 封装了两个电机的操作，提供初始化、清理和测试序列功能
 */
class MotorController {
public:
    /**
     * @brief 初始化电机控制系统
     * 包括电机初始化和信号处理设置
     */
    static void initialize();
    
    /**
     * @brief 清理资源，停止所有电机
     */
    static void cleanup();
    
    /**
     * @brief 运行电机测试序列
     * 使两个电机同步进行加速-减速循环测试
     */
    static void runTestSequence();

    /**
     * @brief 设置左电机速度
     * @param speed 速度百分比(-100~100)
     */
    static void setLeftMotor(int8_t speed);
    
    /**
     * @brief 设置右电机速度
     * @param speed 速度百分比(-100~100)
     */
    static void setRightMotor(int8_t speed);
    
    /**
     * @brief 设置两个电机速度
     * @param leftSpeed 左电机速度(-100~100)
     * @param rightSpeed 右电机速度(-100~100)
     */
    static void setMotors(int8_t leftSpeed, int8_t rightSpeed);
    
    /**
     * @brief 停止所有电机
     */
    static void stopAll();
    
    /**
     * @brief 获取左电机当前速度
     * @return 当前速度百分比(-100~100)
     */
    static int8_t getLeftSpeed();
    
    /**
     * @brief 获取右电机当前速度
     * @return 当前速度百分比(-100~100)
     */
    static int8_t getRightSpeed();
    
    /**
     * @brief 设置全局最大速度限制
     * @param percent 最大速度百分比(0~100)
     */
    static void setMaxSpeed(uint8_t percent);

private:
    /**
     * @brief 电机类，封装单个电机的操作
     */
    class Motor {
    public:
        /**
         * @brief 构造函数
         * @param dir_device 方向控制设备路径
         * @param pwm_device PWM设备路径
         */
        Motor(const char* dir_device, const char* pwm_device);
        
        /**
         * @brief 初始化电机硬件
         */
        void init();
        
        /**
         * @brief 设置电机速度
         * @param duty_percent 占空比百分比(-100~100)，负值表示反转
         */
        void setSpeed(int8_t duty_percent);
        
        /**
         * @brief 停止电机
         */
        void stop();
        
        /**
         * @brief 获取当前速度
         * @return 当前占空比百分比(-100~100)
         */
        int8_t getCurrentSpeed() const;

    private:
        const char* dir_device_;   // 方向控制设备路径
        const char* pwm_device_;   // PWM控制设备路径
        struct pwm_info pwm_info_; // PWM设备信息
        int8_t current_duty_;      // 当前占空比设置
    };

    static Motor motor1;           // 电机1实例
    static Motor motor2;           // 电机2实例
    static uint8_t max_speed_percent_; // 最大速度限制(百分比)

    /**
     * @brief SIGINT信号处理函数
     * @param signum 信号编号
     */
    static void sigintHandler(int signum);
};

#endif // MOTOR_H