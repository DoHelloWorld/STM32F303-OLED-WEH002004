#ifndef __LCD_WEH002004_H_
#define __LCD_WEH002004_H_

#include "stm32f30x_conf.h"
#include "Utils.h"
#include "stdio.h"
#include "string.h"
//#include "RTC.h"



//---Переопределяем порты для подключения дисплея, для удобства---//
#define     LED_PORT              GPIOD
#define     LED_OUT               LED_PORT->ODR
#define     LED_PIN_RS            GPIO_Pin_2          // PB0
#define     LED_PIN_EN            GPIO_Pin_3          // PB1
#define     LED_PIN_D7            GPIO_Pin_7          // PB7
#define     LED_PIN_D6            GPIO_Pin_6          // PB6
#define     LED_PIN_D5            GPIO_Pin_5          // PB5
#define     LED_PIN_D4            GPIO_Pin_4          // PB4
#define     LED_PIN_MASK  ((LED_PIN_RS | LED_PIN_EN | LED_PIN_D7 | LED_PIN_D6 | LED_PIN_D5 | LED_PIN_D4))



//Init delay:
#define     INIT_DELAY           SendByte(0x00, 0)

// Function set:
#define     FUNC_SET_RUS         SendByte(0x2A, 0) //4-бит шина, размер 5x8, шрифты ENG/RUS.
#define     FUNC_SET_ENG         SendByte(0x2C, 0) //4-бит шина, размер 5x8, шрифты ENG.

//Display ON/OFF:
#define     DISPLAY_ON           SendByte(0x0C, 0) //Дисплей ON, Cursor OFF, Blink OFF
#define     DISPLAY_OFF          SendByte(0x08, 0) //Дисплей OFF, Cursor OFF, Blink OFF

//Cursor control:
#define     CURSOR_BLINK         SendByte(0x0F, 0) //Курсор моргает
#define     CURSOR_ON            SendByte(0x0E, 0) //Курсор включен
#define     CURSOR_OFF           SendByte(0x0C, 0) //Курсор выключен

//Entry Mode Set:
#define     ENTRY_INC_ON_SHIFT_OFF  SendByte(0x06, 0) //Cursor decrement ON, Shift OFF

//Clear Display:
#define     CLEAR_DISPLAY        SendByte(0x01, 0)

//Cursor Home:
#define     CURSOR_HOME          SendByte(0x00,0)


#define STACK_SIZE 4


GPIO_InitTypeDef  GPIO_InitStructure;
typedef struct
{
    char FirstMessage[21];
    char SecondMessage[21];
    char ThirdMessage[21];
    char FourthMessage[21];
    int  order[STACK_SIZE];
}StackStruct;




typedef struct
{
    char FirstMessage[21];
    char SecondMessage[21];
    char ThirdMessage[21];
    char FourthMessage[21];
}DisplayStruct;

StackStruct Stack;
DisplayStruct Display;

void delay(int a);
void SendByte(char ByteToSend, int IsData);
void SetCursor(char Row, char Col);
void InitLCD();
void EnableLCD();
void ClearLCD();
void PrintStr(char *Text);
void PushInStack(char* str, int num);
void PopFromStack(int num);
int PrintFromStack(int num);
#endif
