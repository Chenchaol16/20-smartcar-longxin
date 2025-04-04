/*********************************************************************************************************************
* LS2K0300 Opensourec Library 即（LS2K0300 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是LS2K0300 开源库的一部分
*
* LS2K0300 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          zf_driver_delay
* 公司名称          成都逐飞科技有限公司
* 适用平台          LS2K0300
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者           备注
* 2025-02-27        大W            first version
********************************************************************************************************************/

#ifndef _zf_driver_pwm_h
#define _zf_driver_pwm_h


#include "zf_common_typedef.h"

// PWM数据结构体，用于存储PWM相关的参数信息
// 包含频率、占空比、占空比最大值、高电平时间、周期时间、时钟频率等参数
struct pwm_info
{
    uint32 freq;       // PWM频率
    uint32 duty;       // PWM占空比
    uint32 duty_max;   // PWM占空比最大值
    uint32 duty_ns;    // PWM高电平时间（纳秒）
    uint32 period_ns;  // PWM周期时间（纳秒）
    uint32 clk_freq;   // 时钟频率
};

void pwm_get_dev_info(const char *path, struct pwm_info *pwm_info);
void pwm_set_duty(const char *path, uint16 duty);

#endif
