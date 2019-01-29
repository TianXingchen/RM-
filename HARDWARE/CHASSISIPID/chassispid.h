#ifndef __CHASSISPID_H__
#define __CHASSISPID_H__

#include "sys.h"
#include "config.h"


typedef enum{
    CHASSIS_PID_1=0x01,
    CHASSIS_PID_2=0x02,
    CHASSIS_PID_3=0x03,
    CHASSIS_PID_4=0x04
}CHASSIS_PID;

typedef struct{
    float Kp;				//����
    float Ki;				//����
    float Kd;				//΢��
    float error_now;		//�������
    float error_last;		//�ϴ����
    float error_last_last;	//���ϴ����
    int16_t pid_out;		//PID���
}chassisPID_t;				//����ʽPID

int16_t chassisIncPID(CHASSIS_PID PIDNum, int16_t current_velocity,int16_t target_velocity);

chassisPID_t getPIDStruct(CHASSIS_PID PIDNum);
void setPIDParamChange(CHASSIS_PID PIDNum,float KpChange,float KiChange,float KdChange);

#endif

