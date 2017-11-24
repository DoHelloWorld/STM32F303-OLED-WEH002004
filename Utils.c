#include "Utils.h"


void Init_DelayTIM()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	//��������� ������������ �������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	TIM_DeInit(TIM7);

	TIM_TimeBaseStructure.TIM_Prescaler = 72-1 ; //�������� ������� ���� ������������
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //������� ��� ������� 64 ���
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //������� �����
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF; //�� ����� �������� ����� ������� ������
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

	TIM_Cmd(TIM7, ENABLE);
}

void Delay(unsigned short us)
{
    TIM7->CNT = 0;
    while(TIM7->CNT < us);
}

