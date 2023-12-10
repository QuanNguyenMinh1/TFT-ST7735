#ifndef BUTTON_DEBOUNCING_H
#define BUTTON_DEBOUNCING_H

#include "main.h"

typedef struct
{
uint8_t current_sta_button;
uint8_t last_sta_button;
uint8_t filter_button; // trong qua trinh loc nhieu nut nhan//
/*is_debouncing = 1 (at period time of bouncing) and not*/
uint8_t is_debouncing; 
uint32_t debouncing_start_time;
uint8_t is_press_hold;
uint32_t start_press_time;
GPIO_TypeDef *GPIOx;
uint16_t GPIO_Pin;	
}ButtonX;

void button_handle(ButtonX *button_x);
void button_init(ButtonX *button_x, GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);
#endif
