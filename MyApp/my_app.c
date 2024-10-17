#include "my_app.h"
#include "my_key.h"
#include "seg_display.h"


/* @brief ʵ��51�������
#define KEY_UP_PIN      GPIO_PIN_0
#define KEY_DOWN_PIN    GPIO_PIN_1
#define KEY_LEFT_PIN    GPIO_PIN_2
#define KEY_RIGHT_PIN   GPIO_PIN_3
#define KEY_CONFIRM_PIN GPIO_PIN_4

void handleKeyPress(void) {
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_UP_PIN) == GPIO_PIN_SET) {
		// �ϼ������߼�
	}
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_DOWN_PIN) == GPIO_PIN_SET) {
		// �¼������߼�
	}
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_LEFT_PIN) == GPIO_PIN_SET) {
		// ��������߼�
	}
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_RIGHT_PIN) == GPIO_PIN_SET) {
		// �Ҽ������߼�
	}
	if (HAL_GPIO_ReadPin(GPIO_PORT, KEY_CONFIRM_PIN) == GPIO_PIN_SET) {
		// ȷ�ϼ������߼�
	}
}
*/

bool duty_cycle_handled = false;


// Ӧ�ò���ѭ��,��main.c����
void MyApp_Run(void)
{
	// ��ȡ����״̬
	key_main();
	if (key1Info.keyStatus == KEY_PRESSED && !key1Info.key_handled) {
		digCur_position_change(); 
		key1Info.key_handled = true;
	}else if (key1Info.keyStatus == KEY_NOT_PRESSED) {
		key1Info.key_handled = false;
	}

	if (key2Info.keyStatus == KEY_PRESSED && !key2Info.key_handled) {
		increase_value();
		key2Info.key_handled = true;
	}else if (key2Info.keyStatus == KEY_NOT_PRESSED) {
		key2Info.key_handled = false;
	}
	seg_main();

    // ��鰴��״̬
    if (key1Info.keyStatus == KEY_NOT_PRESSED && key2Info.keyStatus == KEY_NOT_PRESSED) {
        // ��ȡ��ǰ��ʾ��ʮ����ֵ
        uint32_t currentDecimalValue = seg_getDisplayDecimal();

        // �������С�ڵ���100������Ϊռ�ձȴ�С
        if (currentDecimalValue <= 100) {
            user_duty_cycle_set(currentDecimalValue); // ��������һ������ռ�ձȵĺ���
			duty_cycle_handled = true;
        }
    }else
		duty_cycle_handled = false;

}


