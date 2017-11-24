#include "lcd_WEH002004.h"

//---Нужная функция для работы с дисплее, по сути дергаем ножкой EN---//
void EnableLCD()
{
   // GPIO_ResetBits(LED_PORT, LED_PIN_EN);
    Delay(200);
    GPIO_SetBits(LED_PORT, LED_PIN_EN);
    Delay(200);
    GPIO_ResetBits(LED_PORT, LED_PIN_EN);
    Delay(200);
}

//---Отсылка байта в дисплей---//
void SendByte(char ByteToSend, int IsData)
{
    LED_OUT &= (~LED_PIN_MASK);
    for( int i = 4; i< 8; i++)
    {
        if((ByteToSend & 0xF0)&(1<<i))
        {
            switch(i)
            {
                case 4 :
                {
                    GPIO_SetBits(LED_PORT, LED_PIN_D4);
                    break;
                }
                case 5 :
                {
                    GPIO_SetBits(LED_PORT, LED_PIN_D5);
                    break;
                }
                case 6:
                {
                    GPIO_SetBits(LED_PORT, LED_PIN_D6);
                    break;
                }
                case 7:
                {
                    GPIO_SetBits(LED_PORT, LED_PIN_D7);
                    break;
                }
                default:
                    break;
            }
        }
        else
        {
            switch(i)
            {
                case 4 :
                {
                    GPIO_ResetBits(LED_PORT, LED_PIN_D4);
                    break;
                }
                case 5 :
                {
                    GPIO_ResetBits(LED_PORT, LED_PIN_D5);
                    break;
                }
                case 6:
                {
                    GPIO_ResetBits(LED_PORT, LED_PIN_D6);
                    break;
                }
                case 7:
                {
                    GPIO_ResetBits(LED_PORT, LED_PIN_D7);
                    break;
                }
                default:
                    break;
            }

        }

    }
    if (IsData == 1)
        GPIO_SetBits(LED_PORT, LED_PIN_RS);
    else
        GPIO_ResetBits(LED_PORT, LED_PIN_RS);
    EnableLCD();
    LED_OUT &= (~LED_PIN_MASK);
    for( int i = 0; i< 4; i++)
    {
        if((ByteToSend)&(1<<i))
        {
            switch(i)
            {
                case 0 :
                {
                    GPIO_SetBits(LED_PORT, LED_PIN_D4);
                    break;
                }
                case 1 :
                {
                    GPIO_SetBits(LED_PORT, LED_PIN_D5);
                    break;
                }
                case 2:
                {
                    GPIO_SetBits(LED_PORT, LED_PIN_D6);
                    break;
                }
                case 3:
                {
                    GPIO_SetBits(LED_PORT, LED_PIN_D7);
                    break;
                }
                default:
                    break;
            }
        }
        else
        {
            switch(i)
            {
                case 0 :
                {
                    GPIO_ResetBits(LED_PORT, LED_PIN_D4);
                    break;
                }
                case 1 :
                {
                    GPIO_ResetBits(LED_PORT, LED_PIN_D5);
                    break;
                }
                case 2:
                {
                    GPIO_ResetBits(LED_PORT, LED_PIN_D6);
                    break;
                }
                case 3:
                {
                    GPIO_ResetBits(LED_PORT, LED_PIN_D7);
                    break;
                }
                default:
                    break;
            }

        }

    }

    if (IsData == 1)
        GPIO_SetBits(LED_PORT, LED_PIN_RS);
    else
        GPIO_ResetBits(LED_PORT, LED_PIN_RS);
    EnableLCD();
}


//---Установка позиции курсора---//
void SetCursor(char Row, char Col)
{
    char address;
    switch(Row)
    {
    case 1:
        {
             address = 0;
            break;
        }
    case 2:
        {
            address = 0x40;
            break;
        }
    case 3:
        {
            address = 0x14;
            break;
        }
    case 4:
        {
            address = 0x54;
            break;
        }
    default:
            break;
    }
    address += Col;
    SendByte(0x80 | address, 0);
}


//---Очистка дисплея---//
void ClearLCD()
{
    CLEAR_DISPLAY;
    Delay(6200);
    CURSOR_HOME;

}

//---Инициализация дисплея---//
void InitLCD(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = LED_PIN_EN | LED_PIN_RS| LED_PIN_D4 | LED_PIN_D5| LED_PIN_D6| LED_PIN_D7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
    LED_OUT &= ~(LED_PIN_MASK);
    GPIO_ResetBits(LED_PORT, LED_PIN_RS);
    GPIO_ResetBits(LED_PORT, LED_PIN_EN);
    INIT_DELAY;
    INIT_DELAY;
    INIT_DELAY;
    INIT_DELAY;
    INIT_DELAY;
    LED_OUT = 0x20;
    EnableLCD();
    FUNC_SET_RUS;
    DISPLAY_ON;
    ClearLCD();
    ENTRY_INC_ON_SHIFT_OFF;

}

//---Печать строки---//
void PrintStr(char *Text)
{
    char *c;
    c = Text;
    while (*c != '\0')
    {
        switch (*c)
        {
            case 'А':
            {
                SendByte(0x41, 1);
                c++;
                break;
            }
            case 'Б':
            {
                SendByte(0xA0, 1);
                c++;
                break;
            }
            case 'В':
            {
                SendByte(0x42, 1);
                c++;
                break;
            }
            case 'Г':
            {
                SendByte(0xA1, 1);
                c++;
                break;
            }
            case 'Д':
            {
                SendByte(0xE0, 1);
                c++;
                break;
            }
            case 'Е':
            {
                SendByte(0x45, 1);
                c++;
                break;
            }
            case 'Ё':
            {
                SendByte(0xB5, 1);
                c++;
                break;
            }
            case 'Ж':
            {
                SendByte(0xA3, 1);
                c++;
                break;
            }
            case 'З':
            {
                SendByte(0xA4, 1);
                c++;
                break;
            }
            case 'И':
            {
                SendByte(0xA5, 1);
                c++;
                break;
            }
            case 'Й':
            {
                SendByte(0xA6, 1);
                c++;
                break;
            }
            case 'К':
            {
                SendByte(0x4B, 1);
                c++;
                break;
            }
            case 'Л':
            {
                SendByte(0b10100111, 1);
                c++;
                break;
            }
            case 'М':
            {
                SendByte(0b01001101, 1);
                c++;
                break;
            }
            case 'Н':
            {
                SendByte(0b01001000, 1);
                c++;
                break;
            }
            case 'О':
            {
                SendByte(0b01001111, 1);
                c++;
                break;
            }
            case 'П':
            {
                SendByte(0b10101000, 1);
                c++;
                break;
            }
            case 'Р':
            {
                SendByte(0b01010000, 1);
                c++;
                break;
            }
            case 'С':
            {
                SendByte(0b01000011, 1);
                c++;
                break;
            }
            case 'Т':
            {
                SendByte(0b01010100, 1);
                c++;
                break;
            }
            case 'У':
            {
                SendByte(0b10101001, 1);
                c++;
                break;
            }
            case 'Ф':
            {
                SendByte(0b10101010, 1);
                c++;
                break;
            }
            case 'Х':
            {
                SendByte(0b01011000, 1);
                c++;
                break;
            }
            case 'Ц':
            {
                SendByte(0b11100001, 1);
                c++;
                break;
            }
            case 'Ч':
            {
                SendByte(0b10101011, 1);
                c++;
                break;
            }
            case 'Ш':
            {
                SendByte(0b10101100, 1);
                c++;
                break;
            }
            case 'Щ':
            {
                SendByte(0b11100010, 1);
                c++;
                break;
            }
            case 'Ъ':
            {
                SendByte(0b10101101, 1);
                c++;
                break;
            }
            case 'Ы':
            {
                SendByte(0b10101110, 1);
                c++;
                break;
            }
            case 'Ь':
            {
                SendByte(0b01100010, 1);
                c++;
                break;
            }
            case 'Э':
            {
                SendByte(0b10101111, 1);
                c++;
                break;
            }
            case 'Ю':
            {
                SendByte(0b10110000, 1);
                c++;
                break;
            }
            case 'Я':
            {
                SendByte(0b10110001, 1);
                c++;
                break;
            }
            case 'а':
            {
                SendByte(0b01100001, 1);
                c++;
                break;
            }
            case 'б':
            {
                SendByte(0b10110010, 1);
                c++;
                break;
            }
            case 'в':
            {
                SendByte(0b10110011, 1);
                c++;
                break;
            }
            case 'г':
            {
                SendByte(0b10110100, 1);
                c++;
                break;
            }
            case 'д':
            {
                SendByte(0b11100011, 1);
                c++;
                break;
            }
            case 'е':
            {
                SendByte(0b01100101, 1);
                c++;
                break;
            }
            case 'ё':
            {
                SendByte(0b10110101, 1);
                c++;
                break;
            }
            case 'ж':
            {
                SendByte(0b10110110, 1);
                c++;
                break;
            }
            case 'з':
            {
                SendByte(0b10110111, 1);
                c++;
                break;
            }
            case 'и':
            {
                SendByte(0b10111000, 1);
                c++;
                break;
            }
            case 'й':
            {
                SendByte(0b10111001, 1);
                c++;
                break;
            }
            case 'к':
            {
                SendByte(0b10111010, 1);
                c++;
                break;
            }
            case 'л':
            {
                SendByte(0b10111011, 1);
                c++;
                break;
            }
            case 'м':
            {
                SendByte(0b10111100, 1);
                c++;
                break;
            }
            case 'н':
            {
                SendByte(0b10111101, 1);
                c++;
                break;
            }
            case 'о':
            {
                SendByte(0b01101111, 1);
                c++;
                break;
            }
            case 'п':
            {
                SendByte(0b10111110, 1);
                c++;
                break;
            }
            case 'р':
            {
                SendByte(0b01110000, 1);
                c++;
                break;
            }
            case 'с':
            {
                SendByte(0b01100011, 1);
                c++;
                break;
            }
            case 'т':
            {
                SendByte(0b10111111, 1);
                c++;
                break;
            }
            case 'у':
            {
                SendByte(0b01111001, 1);
                c++;
                break;
            }
            case 'ф':
            {
                SendByte(0b11100100, 1);
                c++;
                break;
            }
            case 'х':
            {
                SendByte(0b01111000, 1);
                c++;
                break;
            }
            case 'ц':
            {
                SendByte(0b11100101, 1);
                c++;
                break;
            }
            case 'ч':
            {
                SendByte(0b11000000, 1);
                c++;
                break;
            }
            case 'ш':
            {
                SendByte(0b11000001, 1);
                c++;
                break;
            }
            case 'щ':
            {
                SendByte(0b11100110, 1);
                c++;
                break;
            }
            case 'ъ':
            {
                SendByte(0b11000010, 1);
                c++;
                break;
            }
            case 'ы':
            {
                SendByte(0b11000011, 1);
                c++;
                break;
            }
            case 'ь':
            {
                SendByte(0b11000100, 1);
                c++;
                break;
            }
            case 'э':
            {
                SendByte(0b11000101, 1);
                c++;
                break;
            }
            case 'ю':
            {
                SendByte(0b11000110, 1);
                c++;
                break;
            }
            case 'я':
            {
                SendByte(0b11000111, 1);
                c++;
                break;
            }
            case '~':
            {
                SendByte(0b11101111, 1);
                c++;
                break;
            }
            default:
            {
                SendByte(*c, 1);
                c++;
            }
        }
    }
}


void PushInStack(char* str, int num)
{
    int i, n = 0;
    for(int i = 0; i < STACK_SIZE; i++)
    {
        if(Stack.order[i] == num)
        {
            n = STACK_SIZE;
            break;
        }
    }
    if(n != STACK_SIZE)
    {
        for(i = 0; i < STACK_SIZE; i++)
        {
            if(Stack.order[i] == 0)
            {
                Stack.order[i] = num;
                n = i;
                break;
            }
            else
            {
                n = STACK_SIZE;
            }
        }
    }

    switch(n)
    {
        case 0:
        {
            snprintf(Stack.FirstMessage, 21, "%s                     ", str);
            break;
        }
        case 1:
        {
            snprintf(Stack.SecondMessage, 21, "%s                     ", str);
            break;
        }
        case 2:
        {
            snprintf(Stack.ThirdMessage, 21, "%s                     ", str);
            break;
        }
        case 3:
        {
            snprintf(Stack.FourthMessage, 21, "%s                     ", str);
            break;
        }
        default:
            break;
    }

}
void PopFromStack(int num)
{
    int i, n;
    for(i = 0; i < STACK_SIZE; i++)
    {
        if(Stack.order[i] == num)
        {
            Stack.order[i] = 0;
            n = i;
            break;
        }
        else
        {
            n = STACK_SIZE;
        }
    }
    switch(n)
    {
        case 0:
        {
            snprintf(Stack.FirstMessage, 21, "                      ");
            break;
        }
        case 1:
        {
            snprintf(Stack.SecondMessage, 21, "                       ");
            break;
        }
        case 2:
        {
            snprintf(Stack.ThirdMessage, 21, "                      ");
            break;
        }
        case 3:
        {
            snprintf(Stack.FourthMessage, 21, "                      ");
            break;
        }
        default:
            break;
    }
}

int PrintFromStack(int num)
{
    int i;

    for(i = num ; i < STACK_SIZE; i++)
    {
        if((Stack.order[i] != 0) && (num != i))
        {
            num = i;
            break;
        }
        else
        {
            num = STACK_SIZE;
        }
    }
    if(num == STACK_SIZE)
    {
        for(i = 0 ; i < num; i++)
        {
            if((Stack.order[i] != 0) && (num != i))
            {
                num = i;
                break;
            }
            else
            {
                num = STACK_SIZE;
            }
    }
    }
    switch(num)
    {
        case 0:
        {
            snprintf(Display.SecondMessage, 21, "%s                      ", Stack.FirstMessage);
            break;
        }
        case 1:
        {
            snprintf(Display.SecondMessage, 21, "%s                      ", Stack.SecondMessage);
            break;
        }
        case 2:
        {
            snprintf(Display.SecondMessage, 21, "%s                      ", Stack.ThirdMessage);
            break;
        }
        case 3:
        {
            snprintf(Display.SecondMessage, 21, "%s                      ", Stack.FourthMessage);
            break;
        }
        default:
            snprintf(Display.SecondMessage, 21, "                        ");
            break;
    }
    return num;
}
