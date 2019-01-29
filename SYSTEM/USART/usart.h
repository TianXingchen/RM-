#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;   //����״̬���	

//����봮���жϽ��գ��벻Ҫע�����º궨��
void USART1_Init(u32 bound);
void USART1_SendChar(unsigned char b);
void USART1_SendString(uint8_t *buffer,uint16_t len);
#endif
