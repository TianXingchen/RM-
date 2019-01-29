#ifndef __MOTOR_CONTROL_H__
#define __MOTOR_CONTROL_H__

#include "config.h"
#include "CAN.h"
typedef struct{
    struct{
        int16_t  p1;
        int16_t  p2;
        int16_t  p3;
        int16_t  p4;
    }position;	            //底盘电机返回的位置值	
    struct{
        int16_t  v1;
        int16_t  v2;
        int16_t  v3;
        int16_t  v4;
    }velocity;				//底盘电机返回的速度值	
    struct{
        int16_t  c1;
        int16_t  c2;
        int16_t  c3;
        int16_t  c4;
    }current;				//底盘电机输入电流值
    struct{
        int16_t  w1;
        int16_t  w2;
        int16_t  w3;
        int16_t  w4;
    }targetSpeed;				//底盘电机速度给定值
    struct{
        int16_t  VX;
        int16_t  VY;
        int16_t  W0;
    }component;			//底盘电机解算三分量
    struct{
        int16_t  I1;
        int16_t  I2;
        int16_t  I3;
        int16_t  I4;
    }CurrentFeedBack;		//底盘电机电流环反馈分量
}chassisMotorMsg_t;

void CAN1_Init(void);
void sendMotorCurrent(void);
void speedSolving(void);
int8_t chassisSelfCheck(void);

void setMotorCurrentIncrement(int16_t current1,int16_t current2,int16_t current3,int16_t current4);
void setTargetSpeed(int16_t speed1,int16_t speed2,int16_t speed3,int16_t speed4);
void setMotorComponent(int16_t VX,int16_t VY,int16_t W0);

int16_t getMotorVelocity(int num);
int16_t getMotorTargetSpeed(int num);

int16_t chassisCurrentLimit(int16_t current);


#endif
