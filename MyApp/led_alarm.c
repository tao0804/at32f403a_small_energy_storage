#include "my_key.h"
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

// GPIO配置:按键连接在 GPIOA 的 PIN5 和 PIN6
// #define key1_Pin GPIO_PIN_5
// #define key1_GPIO_Port GPIOA
// #define key2_Pin GPIO_PIN_6
// #define key2_GPIO_Port GPIOA


// 按键状态变量
// static uint8_t key1Info.keyStatus = KEY_NOT_PRESSED;
// static uint8_t key2Info.keyStatus = KEY_NOT_PRESSED;

uint8_t key1Info.keyStatus = KEY_NOT_PRESSED;
uint8_t key2Info.keyStatus = KEY_NOT_PRESSED;

static uint64_t key1Info.keyLastReleaseTime = 0;
static uint64_t key2Info.keyLastReleaseTime = 0;

// 按键1扫描函数
uint8_t key1_scan(void)
{
	uint8_t result = key1Info.keyStatus;
	key1Info.keyStatus = KEY_NOT_PRESSED;    // 清除按键状态,避免重复读取
	return result;
}

// 按键2扫描函数
uint8_t key2_scan(void)
{
	uint8_t result = key2Info.keyStatus;
	key2Info.keyStatus = KEY_NOT_PRESSED;
	return result;
}

// 按键状态刷新函数，需在主循环中调用,时间用HAL_GetTick
void key_main(void)
{
	// 检测按键1状态
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == 0) {
		uint32_t currentTime = HAL_GetTick();
		if ((currentTime - key1Info.keyLastReleaseTime) >= 10) {
			key1Info.keyStatus = KEY_PRESSED;
			// 执行对应按键操作
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
			// key1Info.keyLastReleaseTime = currentTime;
		}
	} else {
		key1Info.keyLastReleaseTime = HAL_GetTick();
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);
		key1Info.keyStatus = KEY_NOT_PRESSED;
	}

	// 检测按键2状态
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0) {
		uint32_t currentTime = HAL_GetTick();
		if ((currentTime - key2Info.keyLastReleaseTime) >= 10) {
			key2Info.keyStatus = KEY_PRESSED;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
			// key2Info.keyLastReleaseTime = currentTime;
		}
	}
	else
	{
		key2Info.keyLastReleaseTime = HAL_GetTick();
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
		key2Info.keyStatus = KEY_NOT_PRESSED;
	}
}
