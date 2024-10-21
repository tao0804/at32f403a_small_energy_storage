/*
	@brief 8个单色指示灯,功能为亮灭两种形式
	1.电源开关工作灯:亮正常、灭不工作
	2.太阳能充电灯:亮充电、灭不充电
	3.市电充电灯:亮充电、灭不充电
	4.电池放电灯:亮给一个或多个手机充电、灭没有充电
	5.电源故障灯:亮故障、灭正常
	6.电池欠压灯:亮欠压、灭正常
	7.电池过热灯:亮过热、灭正常
	8.费用到期灯:到期前三天时灯亮，灭时还没有到期
*/
#include "my_led.h"

// 假设每个LED对应一个GPIO引脚，使用一个数组来模拟LED状态 (1: 亮, 0: 灭)
static uint8_t led_states[8] = {0};

// 初始化所有LED (设置为灭)
void led_init(void) {
    for (uint8_t i = 0; i < 8; ++i) {
        led_states[i] = 0;  // 所有LED初始为灭
    }
    printf("LEDs initialized.\n");
}

// 打开指定LED
void led_on(led_type_t led) {
    if (led < 8) {
        led_states[led] = 1;
        printf("LED %d ON\n", led);
    }
}

// 关闭指定LED
void led_off(led_type_t led) {
    if (led < 8) {
        led_states[led] = 0;
        printf("LED %d OFF\n", led);
    }
}

// 切换指定LED的状态(需要吗))
void led_toggle(led_type_t led) {
    if (led < 8) {
        led_states[led] = !led_states[led];
        printf("LED %d TOGGLED to %d\n", led, led_states[led]);
    }
}

// 获取指定LED的状态
uint8_t led_get_state(led_type_t led) {
    if (led < 8) {
        return led_states[led];
    }
    return 0;  // 无效LED时返回0
}



