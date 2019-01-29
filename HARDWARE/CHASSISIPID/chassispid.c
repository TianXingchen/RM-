#include "chassispid.h"

//��ʼ��
const float Kp = 1.40,Ki = 0.07,Kd = 0;

chassisPID_t chassisPID_1 = {Kp,Ki,Kd,0,0,0,0};
chassisPID_t chassisPID_2 = {Kp,Ki,Kd,0,0,0,0};
chassisPID_t chassisPID_3 = {Kp,Ki,Kd,0,0,0,0};
chassisPID_t chassisPID_4 = {Kp,Ki,Kd,0,0,0,0};

chassisPID_t* getPIDStructPointer(CHASSIS_PID num);//�ڲ���������

// ���̵����PID�����������в������κ��޷�;
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
    @ author: ��֮��;
    @ latest  update:2018��10��7��;
    @ function: ��ȡ�������̵����PID�ṹ��ĵ�ַָ��;
    @ param:
        param 1: PIDNum ���̵����ID��;
    @ retval: ��ӦID�ŵĵ��̵����PID�ṹ��ĵ�ַָ��;
    @ note: �ڲ������������⿪��;
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
    @ author: ��֮��;
    @ latest  update:2018��10��7��;
    @ function: ��ȡ�������̵����PID�ṹ��;
    @ param:
        param 1: PIDNum ���̵����ID��;
    @ retval: ��ӦID�ŵĵ��̵����PID�ṹ��;
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
    @ author: ��֮��;
    @ latest  update:2018��10��7��;
    @ function: �޸ĸ������̵����PID����;
    @ param:
        param 1: PIDNum ���̵����ID��;
        param 2: KpChange ��������������;
        param 3: KiChange ���ֲ���������;
        param 4: KdChange ΢�ֲ���������;
*/
void setPIDParamChange(CHASSIS_PID PIDNum,float KpChange,float KiChange,float KdChange){
    chassisPID_t* PID = getPIDStructPointer(PIDNum);
    PID->Kp+=KpChange;
    PID->Ki+=KiChange;
    PID->Kd+=KdChange;
}
