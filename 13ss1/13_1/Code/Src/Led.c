#include "Led.h"
#include "main.h"
#include "Global_Type.h"

#define LED_ON GPIO_PIN_RESET
#define LED_OFF GPIO_PIN_SET

uint16_t Led_Pin[8] = {GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};

static inline void Edit_Led()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);//lock
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);//unlock
}

void Reset_All_Led()
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);
	Edit_Led();
	SettingManager.ledState = 0xff;
}

void Led_Set(uint8_t led, uint8_t state)
{
	HAL_GPIO_WritePin(GPIOC, Led_Pin[led - 1], state);
	Edit_Led();
	uint8_t mask = ~(0x01 << (led - 1));
	SettingManager.ledState = (SettingManager.ledState & mask) | (state << (led - 1));
}

void Led_Set_State(uint8_t state)
{
	for(uint8_t i = 0; i < 8; i++){
		HAL_GPIO_WritePin(GPIOC, Led_Pin[i], (state >> i) & 0x01);
	}
	Edit_Led();
}

void Led_Task()
{
	static uint8_t n = 1;
	if(n < 9)
		Led_Set(n, LED_ON);
	else if(n >= 9)
		Led_Set(n - 8, LED_OFF);
	n++;
	if(n > 16)
		n = 1;
}