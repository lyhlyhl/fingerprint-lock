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
//ALIENTEK Mini STM32开发板扩展实验14
//ATK-AS608指纹识别模块实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司    
//作者：正点原子 @ALIENTEK 

#define usart2_baund  115200//串口2波特率，根据指纹模块波特率更改（注意：指纹模块默认57600）
u16 ValidN;//模块内有效模板个数

void Add_FR(void);	//录指纹
void Del_FR(void);	//删除指纹
void press_FR(void);//刷指纹
void ShowErrMessage(u8 ensure);//显示确认码错误信息
void AS608_load_keyboard(u16 x,u16 y,u8 **kbtbl);//加载虚拟键盘
u8  AS608_get_keynum(u16 x,u16 y);//获取键盘数
u16 GET_NUM(void);//获取数值  

   
int main(void)
{
	u8 ensure;	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init();  	    //初始化延时函数
	usart2_init(usart2_baund); //初始化串口2,用于与指纹模块通讯
	PS_StaGPIO_Init();	      //初始化FR读状态引脚 
   TIM1_PWM_Init(7199,199);  //PWM波输出
   //LED_Init();
   OLED_Init();
   OLED_ON();
   OLED_Fill(0x0);
   while(1)
   {
      TIM_SetCompare1(TIM1,6505);
		if(PS_Sta)	 //检测PS_Sta状态，如果有手指按下
		{
         
			press_FR();//刷指纹	        
		}
      while(PS_Sta == 0);
	} 	
}



//刷指纹
void press_FR(void)
{
	SearchResult seach;
	u8 ensure;
   unsigned char i;
	ensure=PS_GetImage();
	if(ensure==0x00)//获取图像成功 
	{
      OLED_Fill(0x0);
      OLED_ShowStr(0,2,(u8*)getimage,1);
		ensure=PS_GenChar(CharBuffer1);
		if(ensure==0x00) //生成特征成功
		{
         OLED_ShowStr(0,3,(u8*)getcharact,1 );
         LED1 = 1; 
			ensure=PS_HighSpeedSearch(CharBuffer1,0,300,&seach);
			if(ensure==0x00)//搜索成功
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
	 delay_ms(1000);//延时后清除显示
	}
		
}



