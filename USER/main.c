#include "main.h"

//底盘状态变量
CHASSIS_STATE_TYPE CHASSIS_STATE;
// 各模块的初始化程序;
void bspInit(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	USART1_Init(115200);	//串口初始化波特率为115200
	CAN1Init();
	dbusInit();
	TIM14Init();
}
void setChassisState(CHASSIS_STATE_TYPE STATE);

int main(void){
    setChassisState(SELF_CHECK_STATE);
	bspInit();
    //自检循环
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
*************************接口代码区*********************************
******************************************************************/
//设置底盘当前状态
void setChassisState(CHASSIS_STATE_TYPE STATE){
    CHASSIS_STATE = STATE;
}
//获取底盘当前状态
CHASSIS_STATE_TYPE getChassisState(void){
    return CHASSIS_STATE;
}
