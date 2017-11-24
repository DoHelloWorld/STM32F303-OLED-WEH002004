#ifndef __HARDWARE_H_
#define __HARDWARE_H_

#include "stm32f30x_conf.h"
#include "Hardware.h"

void InitHardware()
{
    RCC_DeInit();
    RCC_HSICmd(DISABLE);
    RCC_HSEConfig(RCC_HSE_ON);
    while(!RCC_WaitForHSEStartUp());
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div1);

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

    GPIO_InitTypeDef BUTTONS;

    BUTTONS.GPIO_Pin    = (UP | DOWN | LEFT | RIGHT);
    BUTTONS.GPIO_Speed  = GPIO_Speed_2MHz;
    BUTTONS.GPIO_Mode   = GPIO_Mode_IN;
    BUTTONS.GPIO_PuPd   = GPIO_PuPd_UP;
    GPIO_Init(BUTTON_PORT, &BUTTONS);
}

#endif
