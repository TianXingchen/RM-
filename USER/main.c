#include "main.h"

//����״̬����
CHASSIS_STATE_TYPE CHASSIS_STATE;
// ��ģ��ĳ�ʼ������;
void bspInit(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	USART1_Init(115200);	//���ڳ�ʼ��������Ϊ115200
	CAN1Init();
	dbusInit();
	TIM14Init();
}
void setChassisState(CHASSIS_STATE_TYPE STATE);

int main(void){
    setChassisState(SELF_CHECK_STATE);
	bspInit();
    //�Լ�ѭ��
    while(1){
        if(chassisSelfCheck()){
            setChassisState(NORMAL_STATE);
            break;
        }
    }
	while(1){
		//VisualScope(USART1,chassisMotor.velocity.v1,CurrentSensor_I*1000,ChassisPID_1.Ki*1000,chassisMotor.targetSpeed.w1);
		delay_ms(10);
        
	}
}

/******************************************************************
*************************�ӿڴ�����*********************************
******************************************************************/
//���õ��̵�ǰ״̬
void setChassisState(CHASSIS_STATE_TYPE STATE){
    CHASSIS_STATE = STATE;
}
//��ȡ���̵�ǰ״̬
CHASSIS_STATE_TYPE getChassisState(void){
    return CHASSIS_STATE;
}
