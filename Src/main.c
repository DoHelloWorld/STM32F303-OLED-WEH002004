#include "stm32f30x_conf.h"
#include "Hardware.h"
#include "Utils.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "lcd_WEH002004.h"
#include "stdio.h"



typedef struct menuItem
{
	int id;
	char *name;
	char select;
	struct menuItem *up;
	struct menuItem *right;
	struct menuItem *left;
	struct menuItem *down;
} menuItem;



/*Потоки FreeRTOS*/
void vCheckButtons(void * pvParameters);
void vDisplay(void * pvParameters);
void vMenu(void * pvParameters);

xQueueHandle xButtonsQueue;
xSemaphoreHandle xLCDMutex;

char LCD_Buf[4][21];

int main(void)
{
    xButtonsQueue = xQueueCreate(1, sizeof(int));
    xLCDMutex = xSemaphoreCreateMutex();

    Init_DelayTIM();
    InitHardware();
    InitLCD();
  while(1)
  {
    xTaskCreate(vCheckButtons, "CheckButtons" , configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
    xTaskCreate(vDisplay, "Display", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, NULL);
    xTaskCreate(vMenu, "Menu", configMINIMAL_STACK_SIZE+256, NULL, tskIDLE_PRIORITY+1, NULL);

    vTaskStartScheduler();
  }
}



void vApplicationIdleHook(void)
{

}



void vCheckButtons(void * pvParameters)
{
    portTickType xLastWakenTime;
    xLastWakenTime = xTaskGetTickCount();
    int State = 0;
    while(1)
    {
       /* State = GPIO_ReadInputDataBit(BUTTON_PORT, LEFT) << 0 | GPIO_ReadInputDataBit(BUTTON_PORT, DOWN) << 1 |
                GPIO_ReadInputDataBit(BUTTON_PORT, UP) << 2 | GPIO_ReadInputDataBit(BUTTON_PORT, RIGHT) << 3;*/



        if(!GPIO_ReadInputDataBit(GPIOE, LEFT))
          State |= (1 << 0);
        else
          State &= ~(1 << 0);
        if(!GPIO_ReadInputDataBit(GPIOE, DOWN))
          State |= (1 << 1);
        else
          State &= ~(1 << 1);
        if(!GPIO_ReadInputDataBit(GPIOE, UP))
          State |= (1 << 2);
        else
          State &= ~(1 << 2);
        if(!GPIO_ReadInputDataBit(GPIOE, RIGHT))
          State |= (1 << 3);
        else
          State &= ~(1 << 3);
        xQueueSendToBack(xButtonsQueue, &State, 0);
        vTaskDelayUntil(&xLastWakenTime, 150);
    }
}


void vDisplay(void * pvParameters)
{
    portTickType xLastWakenTime;
    xLastWakenTime = xTaskGetTickCount();
    ClearLCD();
    while(1)
    {
        SetCursor(1,0);
        PrintStr(LCD_Buf[0]);
        SetCursor(2,0);
        PrintStr(LCD_Buf[1]);
        SetCursor(3,0);
        PrintStr(LCD_Buf[2]);
        SetCursor(4,0);
        PrintStr(LCD_Buf[3]);
        vTaskDelayUntil(&xLastWakenTime, 500);
    }
}


void vMenu(void * pvParameters)
{
      menuItem m[6] = { { 1, "  Методики", 0, NULL, NULL, NULL, NULL },
					 {  2, "  Параметры", 0, NULL, NULL, NULL, NULL },
					 {  3, "  Время", 0, NULL, NULL, NULL, NULL },
					 {  4, "  Menu 4", 0, NULL, NULL, NULL, NULL },
					 {  5, "  Menu 5", 0, NULL, NULL, NULL, NULL },
					 {  6, "  Menu 6", 0, NULL, NULL, NULL, NULL } };

	 menuItem m1[3] = {{ 11, "  Методика 1", 1, NULL, NULL, NULL, NULL },
					  { 12, "  Методика 2", 1, NULL, NULL, NULL, NULL },
					  { 13, "  Методика 3", 1, NULL, NULL, NULL, NULL }};



	 menuItem m2[3] = { { 21, "  Датчик", 1, NULL, NULL, NULL, NULL },
					   { 22, "  Магнетроны", 1, NULL, NULL, NULL, NULL },
					   { 23, "  Индикация", 1, NULL, NULL, NULL, NULL } };

	 menuItem m3[3] = { { 31, "  Текущее время", 1, NULL, NULL, NULL, NULL },
					   { 32, "  Текущая дата", 1, NULL, NULL, NULL, NULL },
					   { 33, "  Настройка", 1, NULL, NULL, NULL, NULL } };

	 menuItem m4[3] = { { 41, "  Menu 4-1", 1, NULL, NULL, NULL, NULL },
					   { 42, "  Menu 4-2", 1, NULL, NULL, NULL, NULL },
					   { 43, "  Menu 4-3", 1, NULL, NULL, NULL, NULL } };

	 menuItem m5[3] = { { 51, "  Menu 5-1", 1, NULL, NULL, NULL, NULL },
					   { 52, "  Menu 5-2", 1, NULL, NULL, NULL, NULL },
					   { 53, "  Menu 5-3", 1, NULL, NULL, NULL, NULL } };

	 menuItem m6[3] = { { 61, "  Menu 6-1", 1, NULL, NULL, NULL, NULL },
					   { 62, "  Menu 6-2", 1, NULL, NULL, NULL, NULL },
					   { 63, "  Menu 6-3", 1, NULL, NULL, NULL, NULL } };

    m[0].down = &m[1];
	m[0].right = &m1[0];
	// Настройка М2
	m[1].up = &m[0];
	m[1].right = &m2[0];
	m[1].down = &m[2];
	// Настройка М3
	m[2].up = &m[1];
	m[2].right = &m3[0];
	m[2].down = &m[3];
	// Настройка М4
	m[3].up = &m[2];
	m[3].right = &m4[0];
	m[3].down = &m[4];
	// Настройка М5
	m[4].up = &m[3];
	m[4].right = &m5[0];
	m[4].down = &m[5];
	// Настройка М6
	m[5].up = &m[4];
	m[5].right = &m6[0];

	// Второй уровень меню M1
	// Настройка М11
	m1[0].left = &m[0];
	m1[0].down = &m1[1];
	// Настройка М12
	m1[1].up = &m1[0];
	m1[1].down = &m1[2];
	m1[1].left = &m[0];
	// Настройка М13
	m1[2].up = &m1[1];
	m1[2].left = &m[0];

	// Второй уровень меню M2
	// Настройка М21
	m2[0].left = &m[0];
	m2[0].down = &m2[1];
	// Настройка М22
	m2[1].up = &m2[0];
	m2[1].down = &m2[2];
	m2[1].left = &m[0];
	// Настройка М23
	m2[2].up = &m2[1];
	m2[2].left = &m[0];

	// Второй уровень меню M3
	// Настройка М31
	m3[0].left = &m[0];
	m3[0].down = &m3[1];
	// Настройка М32
	m3[1].up = &m3[0];
	m3[1].down = &m3[2];
	m3[1].left = &m[0];
	// Настройка М33
	m3[2].up = &m3[1];
	m3[2].left = &m[0];

	// Второй уровень меню M4
	// Настройка М41
	m4[0].left = &m[0];
	m4[0].down = &m4[1];
	// Настройка М42
	m4[1].up = &m4[0];
	m4[1].down = &m4[2];
	m4[1].left = &m[0];
	// Настройка М43
	m4[2].up = &m4[1];
	m4[2].left = &m[0];

	// Второй уровень меню M5
	// Настройка М51
	m5[0].left = &m[0];
	m5[0].down = &m5[1];
	// Настройка М52
	m5[1].up = &m5[0];
	m5[1].down = &m5[2];
	m5[1].left = &m[0];
	// Настройка М53
	m5[2].up = &m5[1];
	m5[2].left = &m[0];

	// Второй уровень меню M6
	// Настройка М61
	m6[0].left = &m[0];
	m6[0].down = &m6[1];
	// Настройка М62
	m6[1].up = &m6[0];
	m6[1].down = &m6[2];
	m6[1].left = &m[0];
	// Настройка М63
	m6[2].up = &m6[1];
	m6[2].left = &m[0];

    snprintf(LCD_Buf[0], 21, "Menu                           ");
    snprintf(LCD_Buf[1], 21, "%s                             ", m[0].name);
    snprintf(LCD_Buf[2], 21, "%s                             ", m[1].name);
    snprintf(LCD_Buf[3], 21, "%s                             ", m[2].name);
    LCD_Buf[1][0] = '>';

    menuItem *curItem = &m[0];    // Тут мы будем хранить указатель на текущее меню
    int max_draw_num = 3;
	int select_draw_num = 1;
	int first_draw_num = 1;
	int max_menu_count = 6;
	int max_menu_depth = 2;
	int cur_menu_depth = 1;
    portBASE_TYPE xStatus;
    int StatusRecieved;
    while(1)
    {
        xStatus = xQueueReceive( xButtonsQueue, &StatusRecieved, portMAX_DELAY);
        if(xStatus == pdPASS)
        {
            xSemaphoreTake(xLCDMutex, portMAX_DELAY);
            switch (StatusRecieved)
            {
            case 4:
                if (curItem->up)
                {
                    curItem = curItem->up;
                    if (select_draw_num > 1)
                    {
                        LCD_Buf[select_draw_num - first_draw_num + 1][0] = ' ';
                        select_draw_num--;
                        LCD_Buf[select_draw_num - first_draw_num + 1][0] = '>';
                    }
                    if (select_draw_num > 2)
                    {
                        first_draw_num--;
                        snprintf(LCD_Buf[1], 21, "%s                          ", m[first_draw_num - 1].name);
                        snprintf(LCD_Buf[2], 21, "%s                          ", m[first_draw_num].name);
                        snprintf(LCD_Buf[3], 21, "%s                          ", m[first_draw_num + 1].name);
                        LCD_Buf[select_draw_num - first_draw_num + 1][0] = '>';
                    }

                }
                else
                {
                    NULL;
                }
                break;
            case 8:
                if (curItem->right)
                {
                    curItem = curItem->right;
                    if (cur_menu_depth < max_menu_depth)
                    {
                        cur_menu_depth++;
                        first_draw_num = 1;
                    }
                    switch (select_draw_num)
                    {
                        case 1:
                            snprintf(LCD_Buf[0], 21, "%s                          ", m[0].name+2);
                            snprintf(LCD_Buf[1], 21, "%s                          ", m1[first_draw_num - 1].name);
                            snprintf(LCD_Buf[2], 21, "%s                          ", m1[first_draw_num].name);
                            snprintf(LCD_Buf[3], 21, "%s                          ", m1[first_draw_num + 1].name);
                            LCD_Buf[1][0] = '>';
                            break;
                        case 2:
                            snprintf(LCD_Buf[0], 21, "%s                          ", m[1].name+2);
                            snprintf(LCD_Buf[1], 21, "%s                          ", m2[first_draw_num - 1].name);
                            snprintf(LCD_Buf[2], 21, "%s                          ", m2[first_draw_num].name);
                            snprintf(LCD_Buf[3], 21, "%s                          ", m2[first_draw_num + 1].name);
                            LCD_Buf[1][0] = '>';
                            break;
                        case 3:
                            snprintf(LCD_Buf[0], 21, "%s                          ", m[2].name+2);
                            snprintf(LCD_Buf[1], 21, "%s                          ", m3[first_draw_num - 1].name);
                            snprintf(LCD_Buf[2], 21, "%s                          ", m3[first_draw_num].name);
                            snprintf(LCD_Buf[3], 21, "%s                          ", m3[first_draw_num + 1].name);
                            LCD_Buf[1][0] = '>';
                            break;
                        case 4:
                            snprintf(LCD_Buf[0], 21, "%s                          ", m[3].name+2);
                            snprintf(LCD_Buf[1], 21, "%s                          ", m4[first_draw_num - 1].name);
                            snprintf(LCD_Buf[2], 21, "%s                          ", m4[first_draw_num].name);
                            snprintf(LCD_Buf[3], 21, "%s                          ", m4[first_draw_num + 1].name);
                            LCD_Buf[1][0] = '>';
                            break;
                        case 5:
                            snprintf(LCD_Buf[0], 21, "%s                          ", m[4].name+2);
                            snprintf(LCD_Buf[1], 21, "%s                          ", m5[first_draw_num - 1].name);
                            snprintf(LCD_Buf[2], 21, "%s                          ", m5[first_draw_num].name);
                            snprintf(LCD_Buf[3], 21, "%s                          ", m5[first_draw_num + 1].name);
                            LCD_Buf[1][0] = '>';
                            break;
                        case 6:
                            snprintf(LCD_Buf[0], 21, "%s                          ", m[5].name+2);
                            snprintf(LCD_Buf[1], 21, "%s                          ", m6[first_draw_num - 1].name);
                            snprintf(LCD_Buf[2], 21, "%s                          ", m6[first_draw_num].name);
                            snprintf(LCD_Buf[3], 21, "%s                          ", m6[first_draw_num + 1].name);
                            LCD_Buf[ 1][0] = '>';
                            break;
                    }
                    select_draw_num = 1;
                }
                else
                {
                    NULL;
                }
                break;
            case 1:
                if (curItem->left)
                {
                    curItem = curItem->left;
                    if (cur_menu_depth > 1)
                    {
                        cur_menu_depth--;
                    }
                    first_draw_num = 1;
                    snprintf(LCD_Buf[0], 21, "Menu                          ");
                    snprintf(LCD_Buf[1], 21, "%s                          ", m[first_draw_num - 1].name);
                    snprintf(LCD_Buf[2], 21, "%s                          ", m[first_draw_num].name);
                    snprintf(LCD_Buf[3], 21, "%s                          ", m[first_draw_num + 1].name);
                    LCD_Buf[1][0] = '>';
                    select_draw_num = 1;
                }
                else
                {
                    NULL;
                }
                break;
            case 2:
                if (curItem->down)
                {
                    curItem = curItem->down;
                    if (select_draw_num < max_menu_count)
                    {
                        if (select_draw_num < max_draw_num)
                        {
                            LCD_Buf[select_draw_num - first_draw_num + 1][0] = ' ';
                            select_draw_num++;
                            LCD_Buf[select_draw_num - first_draw_num + 1][0] = '>';
                        }
                        else
                        {
                            select_draw_num++;
                        }
                    }
                    if (select_draw_num > max_draw_num)
                    {
                        first_draw_num++;
                        snprintf(LCD_Buf[1], 21, "%s                          ", m[first_draw_num - 1].name);
                        snprintf(LCD_Buf[2], 21, "%s                          ", m[first_draw_num].name);
                        snprintf(LCD_Buf[3], 21, "%s                          ", m[first_draw_num + 1].name);
                        LCD_Buf[max_draw_num][0] = '>';
                    }
                }
                else
                {
                    NULL;
                }
                break;
            }
            xSemaphoreGive(xLCDMutex);
        }
    }
}
