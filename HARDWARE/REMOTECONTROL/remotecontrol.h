#ifndef __REMOTECONTROL_H__
#define __REMOTECONTROL_H__

#include "config.h"
#include "main.h"


typedef struct{
    uint16_t ch0;
    uint16_t ch1;
    uint16_t ch2;
    uint16_t ch3;
    uint8_t s1;
    uint8_t s2;
} teleControl;	                //遥控器四个通道、两个拨码开关

typedef struct{
    int16_t x;
    int16_t y;
    int16_t z;
    uint8_t press_l;
    uint8_t press_r;
} PCMouseMsg;				//鼠标拖动三分量、左右键点击

typedef struct{
    teleControl teleCtl;	                //遥控器四个通道、两个拨码开关
    PCMouseMsg PCMouse;				//鼠标拖动三分量、左右键点击
    uint16_t PCKey;					//键盘按键
} remoteControl_t;


void dbusInit(void);
uint16_t getRCCtlChannel(int num);
uint16_t getRCCtlswitch(int num);
PCMouseMsg getPCMouseStruct(void);
uint16_t getPCKey(void);
#endif
