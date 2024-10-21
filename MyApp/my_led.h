#ifndef MY_LED_H
#define MY_LED_H

#include <stdio.h>
#include <stdint.h>

// LED枚举定义
typedef enum {
	LED_POWER = 0,       // 电源开关工作灯
	LED_SOLAR_CHARGE,    // 太阳能充电灯
	LED_AC_CHARGE,       // 市电充电灯
	LED_DISCHARGE,       // 电池放电灯
	LED_FAULT,           // 电源故障灯
	LED_UNDERVOLTAGE,    // 电池欠压灯
	LED_OVERHEAT,        // 电池过热灯
	LED_EXPIRED          // 费用到期灯
} led_type_t;

// 初始化所有LED
void led_init(void);

// 打开指定LED
void led_on(led_type_t led);

// 关闭指定LED
void led_off(led_type_t led);

// 切换指定LED的状态
void led_toggle(led_type_t led);

// 获取指定LED的状态 (1: 亮, 0: 灭)
uint8_t led_get_state(led_type_t led);

#endif    // MY_LED_H
