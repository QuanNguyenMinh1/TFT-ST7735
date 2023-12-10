#include "rotary_encoder_volume.h"

__weak void clock_wise_call_back(Rotary_X *p_rt)
{
	
}
__weak void counter_clock_wise_call_back(Rotary_X *p_rt)
{
	
}

void rotary_encoder_volume_init(Rotary_X *p_rt, TIM_HandleTypeDef *htim)
{
	htim->Instance->CNT =0;
	p_rt->counter = 0;
	p_rt->previous_value = 0;
}

void rotary_encoder_volume_handle(Rotary_X *p_rt, TIM_HandleTypeDef *htim)
{
		p_rt->counter = htim->Instance->CNT;
		if(p_rt->previous_value == 0 && p_rt->counter == 65532)
		{
			counter_clock_wise_call_back(p_rt);
			p_rt->previous_value = p_rt->counter;
		}else if (p_rt->previous_value == 6532 && p_rt->counter == 0)
		{
			clock_wise_call_back(p_rt);
			p_rt->previous_value = p_rt->counter;
		}else if (p_rt->previous_value < p_rt->counter)
		{
			clock_wise_call_back(p_rt);
			p_rt->previous_value = p_rt->counter;
		}else if (p_rt->previous_value > p_rt->counter)
		{
			counter_clock_wise_call_back(p_rt);
			p_rt->previous_value = p_rt->counter;
		}
}
