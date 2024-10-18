#ifndef __SEG_DISPLAY_H
#define __SEG_DISPLAY_H

#include "stdbool.h"
#include <stdio.h>
#include <stdint.h>
#include "at32f403a_407_conf.h"


// 段选配置结构体
typedef struct {
	gpio_type *port;
	uint16_t pin;
} SegPinConfig;

extern uint8_t currentDigit;
extern uint8_t segCode_index;

// 段选引脚配置 (A-G和DP)
extern const SegPinConfig segPins[8];

// 位选引脚配置 (D1-D4)
extern const SegPinConfig digitPins[4];

// 宏定义：是否显示首位的0
#define SHOW_LEADING_ZERO 1	// 设置为1显示首位0，设置为0不显示

// 函数声明
void seg_init(void);
void seg_digit_input(uint8_t* inputDigits);
void seg_main(void);


#endif

