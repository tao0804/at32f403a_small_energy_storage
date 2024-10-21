#ifndef MY_KEY_H
#define MY_KEY_H

#include "stdbool.h"
#include <stdio.h>
#include <stdint.h>
#include "at32f403a_407_conf.h"

// 按键状态定义
#define KEY_NOT_PRESSED 0
#define KEY_PRESSED     3

typedef struct KeyInfo {
	uint8_t keyStatus;	// KEY_NOT_PRESSED:未按下 KEY_PRESSED:按下
	uint64_t keyLastReleaseTime;	// 上次释放时间
	bool key_handled;	// 标志位
} KeyInfo_t;

extern KeyInfo_t key0Info, key1Info, key2Info, key3Info, key4Info,
		key5Info, key6Info, key7Info, key8Info, key9Info;


void key_init(void);	// 按键初始化
void key_main(void);	// 按键状态刷新
uint8_t key_scan(void);	// 按键扫描

#endif    // KEY_H

