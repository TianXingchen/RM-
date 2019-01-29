#include "controlloop.h"
/*
    @ author:
    @ latest update:2018年10月7日;
    @ function:整个程序的主控制回路，每1ms执行一次;
    @ param:无;
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
    //自检时底盘不动
    if(getChassisState()==NORMAL_STATE){
        sendMotorCurrent();
    }
}
