#include "chassispid.h"

//初始化
const float Kp = 1.40,Ki = 0.07,Kd = 0;

chassisPID_t chassisPID_1 = {Kp,Ki,Kd,0,0,0,0};
chassisPID_t chassisPID_2 = {Kp,Ki,Kd,0,0,0,0};
chassisPID_t chassisPID_3 = {Kp,Ki,Kd,0,0,0,0};
chassisPID_t chassisPID_4 = {Kp,Ki,Kd,0,0,0,0};

chassisPID_t* getPIDStructPointer(CHASSIS_PID num);//内部函数声明

// 底盘电机的PID控制器，其中不包含任何限幅;
int16_t chassisIncPID(CHASSIS_PID PIDNum, int16_t current_velocity,int16_t target_velocity)
{
    chassisPID_t* PID = getPIDStructPointer(PIDNum);
    PID->error_last_last = PID->error_last;
    PID->error_last = PID->error_now;
    PID->error_now = target_velocity - current_velocity;

    PID->pid_out =  PID->Kp * (PID->error_now - PID->error_last)
		              + PID->Ki * PID->error_now
		              + PID->Kd *( PID->error_now - 2 * PID->error_last + PID->error_last_last);
	
    return PID->pid_out;
}
/*
    @ author: 张之宇;
    @ latest  update:2018年10月7日;
    @ function: 获取各个底盘电机的PID结构体的地址指针;
    @ param:
        param 1: PIDNum 底盘电机的ID号;
    @ retval: 对应ID号的底盘电机的PID结构体的地址指针;
    @ note: 内部函数，不对外开放;
*/
chassisPID_t* getPIDStructPointer(CHASSIS_PID PIDNum){
    switch(PIDNum){
        case 0x01: return &chassisPID_1;break;
        case 0x02: return &chassisPID_2;break;
		case 0x03: return &chassisPID_3;break;
		case 0x04: return &chassisPID_4;break;
    }
    return NULL;
}
/*
    @ author: 张之宇;
    @ latest  update:2018年10月7日;
    @ function: 获取各个底盘电机的PID结构体;
    @ param:
        param 1: PIDNum 底盘电机的ID号;
    @ retval: 对应ID号的底盘电机的PID结构体;
*/
chassisPID_t getPIDStruct(CHASSIS_PID PIDNum){
    switch(PIDNum){
        case 0x01: return chassisPID_1;break;
        case 0x02: return chassisPID_2;break;
        case 0x03: return chassisPID_3;break;
        case 0x04: return chassisPID_4;break;
    }
}
/*
    @ author: 张之宇;
    @ latest  update:2018年10月7日;
    @ function: 修改各个底盘电机的PID参数;
    @ param:
        param 1: PIDNum 底盘电机的ID号;
        param 2: KpChange 比例参数的增量;
        param 3: KiChange 积分参数的增量;
        param 4: KdChange 微分参数的增量;
*/
void setPIDParamChange(CHASSIS_PID PIDNum,float KpChange,float KiChange,float KdChange){
    chassisPID_t* PID = getPIDStructPointer(PIDNum);
    PID->Kp+=KpChange;
    PID->Ki+=KiChange;
    PID->Kd+=KdChange;
}
