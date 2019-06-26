#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "touch.h"	  
#include "usmart.h"  
#include "MMC_SD.h"   
#include "ff.h"  
#include "exfuns.h"    
#include "fontupd.h"
#include "text.h"	
#include "usart2.h"
#include "AS608.h"
#include "timer.h"
#include "led.h"
#include "oled.h"

#define wrongstr "fingerprint is wrong!"
#define fales "fuck off!"
#define truestr "welcome to 3028!"
#define getimage "Get image succeed"
#define getcharact "Creat character!"
#define searchsucceed "find fingerprint!"
//ALIENTEK Mini STM32��������չʵ��14
//ATK-AS608ָ��ʶ��ģ��ʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾    
//���ߣ�����ԭ�� @ALIENTEK 

#define usart2_baund  115200//����2�����ʣ�����ָ��ģ�鲨���ʸ��ģ�ע�⣺ָ��ģ��Ĭ��57600��
u16 ValidN;//ģ������Чģ�����

void Add_FR(void);	//¼ָ��
void Del_FR(void);	//ɾ��ָ��
void press_FR(void);//ˢָ��
void ShowErrMessage(u8 ensure);//��ʾȷ���������Ϣ
void AS608_load_keyboard(u16 x,u16 y,u8 **kbtbl);//�����������
u8  AS608_get_keynum(u16 x,u16 y);//��ȡ������
u16 GET_NUM(void);//��ȡ��ֵ  

   
int main(void)
{
	u8 ensure;	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();  	    //��ʼ����ʱ����
	usart2_init(usart2_baund); //��ʼ������2,������ָ��ģ��ͨѶ
	PS_StaGPIO_Init();	      //��ʼ��FR��״̬���� 
   TIM1_PWM_Init(7199,199);  //PWM�����
   //LED_Init();
   OLED_Init();
   OLED_ON();
   OLED_Fill(0x0);
   while(1)
   {
      TIM_SetCompare1(TIM1,6505);
		if(PS_Sta)	 //���PS_Sta״̬���������ָ����
		{
         
			press_FR();//ˢָ��	        
		}
      while(PS_Sta == 0);
	} 	
}



//ˢָ��
void press_FR(void)
{
	SearchResult seach;
	u8 ensure;
   unsigned char i;
	ensure=PS_GetImage();
	if(ensure==0x00)//��ȡͼ��ɹ� 
	{
      OLED_Fill(0x0);
      OLED_ShowStr(0,2,(u8*)getimage,1);
		ensure=PS_GenChar(CharBuffer1);
		if(ensure==0x00) //���������ɹ�
		{
         OLED_ShowStr(0,3,(u8*)getcharact,1 );
         LED1 = 1; 
			ensure=PS_HighSpeedSearch(CharBuffer1,0,300,&seach);
			if(ensure==0x00)//�����ɹ�
			{
            OLED_ShowStr(0,4,(u8*)searchsucceed,1);
            OLED_ShowStr(0,5,(u8*)truestr,1);
            //TIM_CtrlPWMOutputs(TIM1,ENABLE);
            TIM_SetCompare1(TIM1,6905);
            delay_ms(5000);
            delay_ms(5000);
            delay_ms(5000);
            delay_ms(5000);
            TIM_SetCompare1(TIM1,6505);
           // TIM_CtrlPWMOutputs(TIM1,DISABLE);
			}
			else 
			{
            OLED_ShowStr(0,2,(u8*)wrongstr,1);
            OLED_ShowStr(0,5,(u8*)fales,2);
         }				
	  }
	 delay_ms(1000);//��ʱ�������ʾ
	}
		
}



