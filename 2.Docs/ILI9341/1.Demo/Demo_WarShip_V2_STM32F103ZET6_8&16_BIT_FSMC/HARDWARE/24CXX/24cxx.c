//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F103ZET6,����ԭ��WarShip STM32 V2.x������,��Ƶ72MHZ������12MHZ
//QDtech-TFTҺ������ for STM32 FSMC
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtft.com
//�Ա���վ��http://qdtech.taobao.com
//wiki������վ��http://www.lcdwiki.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567 
//�ֻ�:15989313508���빤�� 
//����:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com 
//����֧��QQ:3002773612  3002778157
//��������QQȺ:324828016
//��������:2018/08/09
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
//All rights reserved
/****************************************************************************************************
//��ģ�����ֱ�Ӳ�������ԭ��WarShip STM32 V2.x������TFTLCD��ۣ������ֶ�����
//STM32����������ָTFTLCD��������ڲ����ӵ�STM32����
//=========================================��Դ����================================================//
//     LCDģ��             TFTLCD�������        STM32��������
//      VDD       --->         5V/3.3              DC5V/3.3V          //��Դ
//      GND       --->          GND                  GND              //��Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������Ϊ16λ��������
//     LCDģ��             TFTLCD�������        STM32��������
//      DB0       --->          D0                   PD14        -|   
//      DB1       --->          D1                   PD15         |  
//      DB2       --->          D2                   PD0          | 
//      DB3       --->          D3                   PD1          | 
//      DB4       --->          D4                   PE7          |
//      DB5       --->          D5                   PE8          |
//      DB6       --->          D6                   PE9          |
//      DB7       --->          D7                   PE10         |
//���ʹ��8λģʽ����ʹ�������8λ������������                    |===>Һ����16λ���������ź�
//      DB8       --->          D8                   PE11         |
//      DB9       --->          D9                   PE12         |
//      DB10      --->          D10                  PE13         |
//      DB11      --->          D11                  PE14         |
//      DB12      --->          D12                  PE15         |
//      DB13      --->          D13                  PD8          |
//      DB14      --->          D14                  PD9          |
//      DB15      --->          D15                  PD10        -|
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 				     TFTLCD�������        STM32�������� 
//       WR       --->          WR                   PD5             //Һ����д���ݿ����ź�
//       RD       --->          RD                   PD4             //Һ���������ݿ����ź�
//       RS       --->          RS                   PG0             //Һ��������/��������ź�
//       RST      --->          RST                ��λ����          //Һ������λ�����ź�
//       CS       --->          CS                   PG12            //Һ����Ƭѡ�����ź�
//       BL       --->          BL                   PB0             //Һ������������ź�
//=========================================������������=========================================//
//���ģ�鲻���������ܻ��ߴ��д������ܣ����ǲ���Ҫ�������ܣ�����Ҫ���д���������
//	   LCDģ��             TFTLCD�������        STM32�������� 
//      PEN       --->          PEN                  PF10            //�����������ж��ź�
//      MISO      --->          MISO                 PF8             //������SPI���߶��ź�
//      MOSI      --->          MOSI                 PF9             //������SPI����д�ź�
//      T_CS      --->          TCS                  PB2             //������Ƭѡ�����ź�
//      CLK       --->          CLK                  PB1             //������SPI����ʱ���ź�
**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/			
#include "24cxx.h" 
#include "delay.h"

/*****************************************************************************
 * @name       :void AT24CXX_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialize IIC interface
 * @parameters :None
 * @retvalue   :None
******************************************************************************/ 
void AT24CXX_Init(void)
{
	IIC_Init();
}

/*****************************************************************************
 * @name       :u8 AT24CXX_ReadOneByte(u16 ReadAddr)
 * @date       :2018-08-09 
 * @function   :Read out a data at a specified address in the AT24CXX
 * @parameters :ReadAddr:the address of start reading
 * @retvalue   :Read data
******************************************************************************/ 
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//���͸ߵ�ַ
		IIC_Wait_Ack();		 
	}else IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	 

	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //�������ģʽ			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}

/*****************************************************************************
 * @name       :void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
 * @date       :2018-08-09 
 * @function   :Write a data at a specified address in AT24CXX
 * @parameters :WriteAddr:the destination address for writing data
								DataToWrite:Data to be written
 * @retvalue   :None
******************************************************************************/ 
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	    //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//���͸ߵ�ַ
		IIC_Wait_Ack();		 
	}else
	{
		IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 
	}	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //�����ֽ�							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}

/*****************************************************************************
 * @name       :void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
 * @date       :2018-08-09 
 * @function   :begins to write data with a length of Len 
								at the specified address in the AT24CXX
 * @parameters :WriteAddr:the address to start writing
								DataToWrite:the header address of the data array 
								Len:Length of data to be written(2 or 4)
 * @retvalue   :None
******************************************************************************/ 
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

/*****************************************************************************
 * @name       :u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
 * @date       :2018-08-09 
 * @function   :begins to read data with a length of Len 
								at the specified address in the AT24CXX,
								used to read 16bits or 32bits data
 * @parameters :ReadAddr:the address of start reading
								len:Length of data to be read(2 or 4)
 * @retvalue   :Read data
******************************************************************************/ 
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}

/*****************************************************************************
 * @name       :u8 AT24CXX_Check(void)
 * @date       :2018-08-09 
 * @function   :Check that AT24CXX is normal or not,
								Use AT24CXX's last address (255) to store the token,
								if use the other 24C series, this address needs to be modified,
 * @parameters :None
 * @retvalue   :0-check successfully
								1-check failed
******************************************************************************/
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp=AT24CXX_ReadOneByte(255);//����ÿ�ο�����дAT24CXX			   
	if(temp==0X55)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		AT24CXX_WriteOneByte(255,0X55);
	    temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

/*****************************************************************************
 * @name       :void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
 * @date       :2018-08-09 
 * @function   :begins to read out the specified number of data at 
								the specified address in the AT24CXX
 * @parameters :ReadAddr:the address of start reading,it is 0~255 for 24c02
								pBuffer:the header address of the data array 
								NumToRead:Number of data to be read
 * @retvalue   :None
******************************************************************************/
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
} 

/*****************************************************************************
 * @name       :void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
 * @date       :2018-08-09 
 * @function   :begins to write the specified number of data at 
								the specified address in the AT24CXX
 * @parameters :WriteAddr:the address of start writing,it is 0~255 for 24c02
								pBuffer:the header address of the data array 
								NumToRead:Number of data to be writen
 * @retvalue   :None
******************************************************************************/ 
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
 











