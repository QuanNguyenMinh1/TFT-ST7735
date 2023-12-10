#include "button_debouncing.h"

__weak void button_pressed_call_back(ButtonX *button_x)
{
}
__weak void button_release_call_back(ButtonX *button_x)
{
}
__weak void button_press_short_call_back(ButtonX *button_x)
{
}
__weak void button_press_hold_call_back(ButtonX *button_x)
{
}
void button_handle(ButtonX *button_x)
{
	/*Debouncing*/
	uint8_t sta = HAL_GPIO_ReadPin(button_x->GPIOx, button_x->GPIO_Pin);
	
	if (sta != button_x->filter_button)
	{
		button_x->filter_button = sta;
		button_x->is_debouncing = 1;
		button_x->debouncing_start_time = HAL_GetTick();
	}
	/*stable button status*/
	if ((button_x->is_debouncing == 1) && ((HAL_GetTick() - button_x->debouncing_start_time) >= 15))
	{
		button_x->current_sta_button = button_x->filter_button;
		button_x->is_debouncing = 0;
	}
	/*Handle event*/
	if (button_x->current_sta_button != button_x->last_sta_button)
	{
		if (button_x->current_sta_button == 0)
		{
			/*is pressed*/
			button_pressed_call_back(button_x);
			button_x->start_press_time = HAL_GetTick();
			button_x->is_press_hold = 1;
		}else {
			/*is release*/
			if (HAL_GetTick() - button_x->start_press_time <= 1000)
			{
				button_press_short_call_back(button_x);
			}
			button_release_call_back(button_x);
			button_x->is_press_hold = 0;
		}
		button_x->last_sta_button = button_x->current_sta_button;
	}
	if ((button_x->is_press_hold == 1) && ((HAL_GetTick() - button_x->start_press_time) >= 3000))
	{
		button_press_hold_call_back(button_x);
		button_x->is_press_hold = 0;
	}
	
}

void button_init(ButtonX *button_x, GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	/*  initial status of button */
	button_x->current_sta_button = 1; 
	button_x->filter_button = 1;
	button_x->last_sta_button = 1;
	button_x->GPIOx = GPIOx;
	button_x->GPIO_Pin = GPIO_Pin;
}
