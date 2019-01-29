#ifndef	__CONFIG_H__
#define	__CONFIG_H__

#include "stm32f4xx.h"
#include "sys.h" 
#include "delay.h"
#include "usart.h"


#define MAX_INTIGRATION 			100		//积分限幅
#define MAX_CURRENT 				4000	//电流输出限幅
#define coefficient 				0.3		//电流反馈系数
#define Imax 						2.3		//电流环临界最大电流
#define Imin 						-2.3	//电流环临界最小电流
#define L0              0.08  //RM2018赛季步兵底盘纵向偏心尺寸/(m)
#define L1							0.177	//RM2018赛季步兵底盘纵向尺寸/2(m)
#define L2							0.172	//RM2018赛季步兵底盘横向尺寸/2(m)
#define WHEEL_DIAMETER							1.52	//麦轮直径(dm)
/* ----------------------- RC Channel Definition---------------------------- */
#define RC_CH_VALUE_MIN 			((uint16_t)364 )
#define RC_CH_VALUE_OFFSET 			((uint16_t)1024)
#define RC_CH_VALUE_MAX 			((uint16_t)1684)
/* ----------------------- RC Switch Definition----------------------------- */
#define RC_SW_UP 					((uint16_t)1)
#define RC_SW_MID 					((uint16_t)3)
#define RC_SW_DOWN 					((uint16_t)2)
/* ----------------------- PC Key Definition-------------------------------- */
#define KEY_PRESSED_OFFSET_W 		((uint16_t)0x01<<0)
#define KEY_PRESSED_OFFSET_S 		((uint16_t)0x01<<1)
#define KEY_PRESSED_OFFSET_A 		((uint16_t)0x01<<2)
#define KEY_PRESSED_OFFSET_D 		((uint16_t)0x01<<3)
#define KEY_PRESSED_OFFSET_Q 		((uint16_t)0x01<<4)
#define KEY_PRESSED_OFFSET_E 		((uint16_t)0x01<<5)
#define KEY_PRESSED_OFFSET_SHIFT 	((uint16_t)0x01<<6)
#define KEY_PRESSED_OFFSET_CTRL 	((uint16_t)0x01<<7)


#endif
