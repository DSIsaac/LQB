#ifndef LED_H
#define LED_H

#include <stdint.h>

void Reset_All_Led(void);

void Led_Set_State(uint8_t state);
void Led_Task();

#endif