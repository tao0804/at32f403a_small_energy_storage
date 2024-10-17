/**************
	@brief 数码管基本只显示数字,若扩展可以显示摄氏度(℃),电流(A),电压(V),时长(h)
**************/
#include "seg_display.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "math.h"

// 8位数码管的段选与位选具体io确定mcu之后确定

// 段选引脚配置数组
const SegPinConfig segPins[8] = {
	{GPIOB, GPIO_PIN_9 }, // SEG_A
	{GPIOA, GPIO_PIN_15}, // SEG_B
	{GPIOB, GPIO_PIN_4 }, // SEG_C
	{GPIOB, GPIO_PIN_6 }, // SEG_D
	{GPIOB, GPIO_PIN_7 }, // SEG_E
	{GPIOB, GPIO_PIN_8 }, // SEG_F
	{GPIOB, GPIO_PIN_3 }, // SEG_G
	{GPIOB, GPIO_PIN_5 }  // SEG_DP
};

// 位选引脚配置数组
const SegPinConfig digitPins[4] = {
	{GPIOA, GPIO_PIN_11},	// DIGIT_1
	{GPIOA, GPIO_PIN_12},	// DIGIT_2
	{GPIOC, GPIO_PIN_13},	// DIGIT_3
	{GPIOC, GPIO_PIN_14},	// DIGIT_4
	{GPIOA, GPIO_PIN_11},	// DIGIT_5
	{GPIOA, GPIO_PIN_12},	// DIGIT_6
	{GPIOC, GPIO_PIN_13},	// DIGIT_7
	{GPIOC, GPIO_PIN_14} 	// DIGIT_8
};

// 数码管段码表
static uint8_t segCode[] = {
	0xC0,	// 0
	0xF9,	// 1
	0xA4,	// 2
	0xB0,	// 3
	0x99,	// 4
	0x92,	// 5
	0x82,	// 6
	0xF8,	// 7
	0x80,	// 8
	0x90, 	// 9
	// 0x88,	//A
	// 0x83,	//B
	// 0xc6,	//C
	// 0xa1,	//D
	// 0x86,	//E
	// 0x8e,	//F
	// 0x8c,	//P
	// 0xc1,	//U
	// 0x91,	//Y
	// 0x7c,	//L
	0x00,	//全亮
	0xff	//熄灭
	
};


uint8_t currentDigit = 0;
uint8_t segCode_index = 0;
uint8_t position = 0;

static uint64_t digLastUpdateTime = 0;

// static uint8_t pointState[4] = {0, 0, 0, 0};
static uint8_t displayNum[4] = {0, 0, 0, 0};

// 实际是面板按键,应用层用key接口替换uint8_t* inputDigits
void seg_digit_input(uint8_t* inputDigits)
{
    for (int i = 0; i < 8; i++) {
        // 保证输入数字在0~9范围内
        if (inputDigits[i] >= 0 && inputDigits[i] <= 9) {
            displayNum[i] = inputDigits[i];
        } else {
            displayNum[i] = 0xFF; // 非法输入处理为熄灭
        }
    }
}

// 数码管显示刷新
void seg_main(void)
{
	// uint32_t currentTime = HAL_GetTick();
	uint32_t currentTime = HAL_GetTick();

	// 检查是否已经过了10ms
	if ((currentTime - digLastUpdateTime) >= 10)
	{
		// 获取当前位需要显示的数字
		uint8_t code = segCode[displayNum[currentDigit]];

		// 如果当前位启用小数点,将小数点段位设置为1
		if (pointState[currentDigit]) {
			code &= 0x7F;
		}

		// 关闭所有位选
		for (int i = 0; i < 4; i++) {
			HAL_GPIO_WritePin(digitPins[i].port, digitPins[i].pin, GPIO_PIN_SET);
		}

		// 设置段选引脚
		for (int i = 0; i < 8; i++) {
			if (code & (1 << i)) {
				HAL_GPIO_WritePin(segPins[i].port, segPins[i].pin, GPIO_PIN_SET);
			} else {
				HAL_GPIO_WritePin(segPins[i].port, segPins[i].pin, GPIO_PIN_RESET);
			}
		}

		// 打开当前位选
		HAL_GPIO_WritePin(digitPins[currentDigit].port, digitPins[currentDigit].pin, GPIO_PIN_RESET);

		// 更新当前位
		currentDigit = (currentDigit + 1) % 4;
		digLastUpdateTime = currentTime;
	}
}


