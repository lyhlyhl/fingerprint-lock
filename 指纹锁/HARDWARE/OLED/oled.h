#ifndef __OLED_H
#define __OLED_H	 
#include "sys.h"
/**********************************************修改区************************************************/
//SCL PB6    SDA PB7
#define RCC_APB2Periph_OLED_SCL_PORT			RCC_APB2Periph_GPIOA			//RCC_APB2Periph_GPIOA~G
#define GPIO_OLED_SCL_PORT								GPIOA											//GPIOA~G
#define GPIO_Pin_OLED_SCL									GPIO_Pin_4								//GPIO_Pin_0~15

#define RCC_APB2Periph_OLED_SDA_PORT			RCC_APB2Periph_GPIOA			//RCC_APB2Periph_GPIOA~G
#define GPIO_OLED_SDA_PORT								GPIOA											//GPIOA~G
#define GPIO_Pin_OLED_SDA									GPIO_Pin_6							//GPIO_Pin_0~15


#define OLED_IIC_SCL											PAout(4)//SCL
#define OLED_IIC_SDA											PAout(6)//SDA
#define	OLED_READ_SDA											PAin(6)	//SDA状态读取
/*****************************************************************************************************/

#define OLED_ADDRESS	0x78 //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define SIZE 		16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

/////////////////////////////////////////////////////////////
//OLED_IIC协议函数///////////////////////////////////////////
void OLED_SDA_IN(void);
void OLED_SDA_OUT(void);
void OLED_IIC_Init(void);
void OLED_IIC_Start(void);
void OLED_IIC_Stop(void);
void OLED_IIC_ACK(void);
void OLED_IIC_NACK(void);
unsigned char OLED_IIC_Wait_Ack(void);
void OLED_IIC_Write_Byte(unsigned char data);
void OLED_IIC_Write_Data(unsigned char Device_addr,unsigned char Reg_addr,unsigned char data);
unsigned char OLED_IIC_Read_Byte(unsigned char Ack_EN);
unsigned char OLED_IIC_Read_Data(unsigned char Device_addr,unsigned char Reg_addr,unsigned char ACK_EN);
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//OLED控制用函数///////////////////////////////////////////
void OLED_WriteCmd(unsigned char I2C_Command);						// -- 写命令
void OLED_WriteDat(unsigned char I2C_Data);							//-- 写数据
void OLED_Init(void);																//-- OLED屏初始化
void OLED_SetPos(unsigned char x, unsigned char y);	//-- 设置起始点坐标
void OLED_Fill(unsigned char fill_Data);						//-- 全屏填充  0xff
void OLED_CLS(void);																//-- 清屏
void OLED_ON(void);																	//-- 唤醒
void OLED_OFF(void);																//-- 睡眠
void OLED_Refresh_Gram(void);														//-- 刷屏
/*-- 显示字符串(字体大小有6*8和8*16两种)****/
//只显示字符串不显示变量
/*-- 例如OLED_ShowStr(0,0,"abc",2);*/
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);		

/*-- 显示中文(中文需要先取模，然后放到codetab.h中*/
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);

/*-- 显示-- BMP图片*/
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

#endif

