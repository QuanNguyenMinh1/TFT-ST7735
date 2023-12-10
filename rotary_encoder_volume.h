#ifndef  ROTARY_ENCODER_VOLUME_H
#define	 ROTARY_ENCODER_VOLUME_H

#include "stm32f1xx_hal.h"


typedef struct
{	
	volatile uint16_t counter;
	uint16_t previous_value;
}Rotary_X;


void rotary_encoder_volume_init(Rotary_X *p_rt, TIM_HandleTypeDef *htim);
void rotary_encoder_volume_handle(Rotary_X *p_rt,TIM_HandleTypeDef *htim);	
#endif
