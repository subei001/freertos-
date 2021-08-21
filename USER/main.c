#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hwjs.h"
#include "lcd.h"
#include "exti.h"
#include "key.h"
/************************************************
 ALIENTEK ս��STM32F103������ FreeRTOSʵ��4-1
 FreeRTOS�жϲ���-�⺯���汾
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

//�������ȼ�
#define START_TASK_PRIO			1
//�����ջ��С	
#define START_STK_SIZE 			256  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define INTERRUPT_TASK_PRIO		2
//�����ջ��С	
#define INTERRUPT_STK_SIZE 		256  
//������
TaskHandle_t INTERRUPTTask_Handler;
//������
void interrupt_task(void *p_arg);


//LCDˢ��ʱʹ�õ���ɫ
int lcd_discolor[14]={	WHITE, BLACK, BLUE,  BRED,      
						GRED,  GBLUE, RED,   MAGENTA,       	 
						GREEN, CYAN,  YELLOW,BROWN, 			
						BRRED, GRAY };

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4	 
	delay_init();	    				//��ʱ������ʼ��	 
	uart_init(115200);					//��ʼ������
	EXTIX_Init();		//�ⲿ�жϳ�ʼ��
//	Hwjs_Init();
	LED_Init();		  					//��ʼ��LED
		LCD_Init();							//��ʼ��LCD
	  LED0=0;				//����LED
//	TIM3_Int_Init(10000-1,7200-1);		//��ʼ����ʱ��3����ʱ������1S
//	TIM5_Int_Init(10000-1,7200-1);		//��ʼ����ʱ��5����ʱ������1S
	
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //�����жϲ�������
    xTaskCreate((TaskFunction_t )interrupt_task,  			//������
                (const char*    )"interrupt_task", 			//��������
                (uint16_t       )INTERRUPT_STK_SIZE,		//�����ջ��С
                (void*          )NULL,						//���ݸ��������Ĳ���
                (UBaseType_t    )INTERRUPT_TASK_PRIO,		//�������ȼ�
                (TaskHandle_t*  )&INTERRUPTTask_Handler); 	//������
	vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

//�жϲ��������� 
void interrupt_task(void *pvParameters)
{
	static u32 total_num=0;
		u8 task1_num=0;
	
	POINT_COLOR = BLACK;

	LCD_DrawRectangle(5,110,115,314); 	//��һ������	
	LCD_DrawLine(5,130,115,130);		//����
	POINT_COLOR = BLUE;
	LCD_ShowString(6,111,110,16,16,"Task1 Run:000");
//	portENABLE_INTERRUPTS();
    while(1)
     {

//		if(hw_jsbz==1) 
//		{
//			LCD_ShowString(6,150,110,16,16,"666\r\n");
//			total_num+=1;

//			printf("%d",total_num);	//���ж�
//			hw_jsbz=0;
//		}
//        LED0=~LED0;
        vTaskDelay(1000);
    }
} 

