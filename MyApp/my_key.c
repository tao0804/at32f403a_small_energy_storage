#include "my_key.h"
#include "at32f403a_407_gpio.h"

// GPIO配置:按键0~9

KeyInfo_t key0Info, key1Info, key2Info, key3Info, key4Info,
		key5Info, key6Info, key7Info, key8Info, key9Info;


void key_init(void)
{
	memset(&key1Info, 0, sizeof(key1Info));
	memset(&key2Info, 0, sizeof(key2Info));
}


// 按键状态刷新函数，需在主循环中调用,时间用HAL_GetTick
void key_main(void)
{
	// 确定对应io即按类似操作,注意上下拉

	// 检测按键1状态
	if (gpio_output_data_bit_read(GPIOA, GPIO_PINS_5) == 0) {
		uint32_t currentTime = HAL_GetTick();
		if ((currentTime - key1Info.keyLastReleaseTime) >= 10) {
			key1Info.keyStatus = KEY_PRESSED;
			// 执行对应按键操作
			gpio_bits_write(GPIOD, GPIO_PINS_1, FALSE);
		}
	} else {
		key1Info.keyLastReleaseTime = HAL_GetTick();
		gpio_bits_write(GPIOD, GPIO_PINS_1, TRUE);
		key1Info.keyStatus = KEY_NOT_PRESSED;
	}

	// 检测按键2状态
	if (gpio_output_data_bit_read(GPIOA, GPIO_PINS_6) == 0) {
		uint32_t currentTime = HAL_GetTick();
		if ((currentTime - key2Info.keyLastReleaseTime) >= 10) {
			key2Info.keyStatus = KEY_PRESSED;
			gpio_bits_write(GPIOA, GPIO_PINS_8, FALSE);
		}
	}
	else
	{
		key2Info.keyLastReleaseTime = HAL_GetTick();
		gpio_bits_write(GPIOA, GPIO_PINS_8, TRUE);
		key2Info.keyStatus = KEY_NOT_PRESSED;
	}
}
