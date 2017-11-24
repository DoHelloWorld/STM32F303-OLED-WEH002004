#include "Utils.h"


void Init_DelayTIM()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	//¬ключение тактировани€ таймера
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	TIM_DeInit(TIM7);

	TIM_TimeBaseStructure.TIM_Prescaler = 72-1 ; //делитель частоты шины тактировани€
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //частота без делени€ 64 ћгц
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //считаем вверх
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF; //до этого значени€ будет считать таймер
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

	TIM_Cmd(TIM7, ENABLE);
}

void Delay(unsigned short us)
{
    TIM7->CNT = 0;
    while(TIM7->CNT < us);
}

