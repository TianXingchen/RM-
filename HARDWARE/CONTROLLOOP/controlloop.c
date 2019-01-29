#include "controlloop.h"
/*
    @ author:
    @ latest update:2018��10��7��;
    @ function:��������������ƻ�·��ÿ1msִ��һ��;
    @ param:��;
*/
void controlLoop(void){
    setMotorComponent(
        (getRCCtlChannel(2)-1024)*10,
       -(getRCCtlChannel(3)-1024)*10,
        (getRCCtlChannel(0)-1024)*10
    );
    setMotorCurrentIncrement(
        chassisIncPID(CHASSIS_PID_1,getMotorVelocity(1),getMotorTargetSpeed(1)),
        chassisIncPID(CHASSIS_PID_2,getMotorVelocity(2),getMotorTargetSpeed(2)),
        chassisIncPID(CHASSIS_PID_3,getMotorVelocity(3),getMotorTargetSpeed(3)),
        chassisIncPID(CHASSIS_PID_4,getMotorVelocity(4),getMotorTargetSpeed(4))
    );
    //�Լ�ʱ���̲���
    if(getChassisState()==NORMAL_STATE){
        sendMotorCurrent();
    }
}
