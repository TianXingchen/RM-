#include "motorcontrol.h"

//�ĸ��������̨ͨѶ�����Լ�ṹ��
typedef struct{
    uint8_t motor1Connection;
    uint8_t motor2Connection;
    uint8_t motor3Connection;
    uint8_t motor4Connection;
    uint8_t gimbalConnection;
}connectionState_t;

//��ʼ������
chassisMotorMsg_t chassisMotor={	
							 {0,0,0,0},
							 {0,0,0,0},
							 {0,0,0,0},
							 {0,0,0,0},	
							 {0,0,0},
							 {0,0,0,0}
};
connectionState_t connectionState={0,0,0,0,0};

void CAN1_TX_IRQHandler(void){ //CAN TX
    if (CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET){
        CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
    }
}

void CAN1_RX0_IRQHandler(void){
    CanRxMsg RxMessage;
    if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET){
        CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
        CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);  
		
        //����������̨��·������ݣ�0x401
        
        if(RxMessage.StdId == 0x401){
            connectionState.gimbalConnection = 0x01;
            chassisMotor.component.VY = -(RxMessage.Data[0]<<8 | RxMessage.Data[1]);//�������
            chassisMotor.component.VX =   RxMessage.Data[2]<<8 | RxMessage.Data[3];//�������
            chassisMotor.component.W0 =   RxMessage.Data[4]<<8 | RxMessage.Data[5];//��ת����
        }
        
        //�������Ե��̵�������ݣ�0x201~0x204
        if(RxMessage.StdId == 0x201){
            connectionState.motor1Connection = 0x01;
            chassisMotor.position.p1 = RxMessage.Data[0]<<8 | RxMessage.Data[1];//0~8191
            chassisMotor.velocity.v1 = RxMessage.Data[2]<<8 | RxMessage.Data[3];//prm
        }
        if(RxMessage.StdId == 0x202){
            connectionState.motor2Connection = 0x01;
            chassisMotor.position.p2 = RxMessage.Data[0]<<8 | RxMessage.Data[1];//0~8191
            chassisMotor.velocity.v2 = RxMessage.Data[2]<<8 | RxMessage.Data[3];//prm
        }
        if(RxMessage.StdId == 0x203){
            connectionState.motor3Connection = 0x01;
            chassisMotor.position.p3 = RxMessage.Data[0]<<8 | RxMessage.Data[1];//0~8191
            chassisMotor.velocity.v3 = RxMessage.Data[2]<<8 | RxMessage.Data[3];//prm
        }
        if(RxMessage.StdId == 0x204){
            connectionState.motor4Connection = 0x01;
            chassisMotor.position.p4 = RxMessage.Data[0]<<8 | RxMessage.Data[1];//0~8191
            chassisMotor.velocity.v4 = RxMessage.Data[2]<<8 | RxMessage.Data[3];//prm
        }
    }
}

/*
    @ author:
    @ latest  update:2018��10��7��;
    @ function: ͨ��can1�������ݸ����̵�����������Ƶ��̵��˶�;
    @ param: ��;
    @ note: �ĸ����͵���ֵ�ķ�ΧΪ-16384~16384;
*/
void sendMotorCurrent(void){
    CANSendData8(0x200,chassisMotor.current.c1,chassisMotor.current.c2,chassisMotor.current.c3,chassisMotor.current.c4);
}

/*
    @ author: ����
    @ latest  update:2018��10��7��;
    @ function: ���̵��ٶȷ������㣬
        ��ƽ���ƶ�����Ԫ�ؽ���Ϊ�ĸ����ֵ���ĸ���ת��;
    @ param: ��;
    @ note: �ý��㺯��������ƫ����ת;
*/
void speedSolving(void){
    int16_t Vx=chassisMotor.component.VX;
    int16_t Vy=chassisMotor.component.VY;
    int16_t W0=chassisMotor.component.W0;
    chassisMotor.targetSpeed.w1 =  (Vy + Vx + W0 * (L1 + L2 - L0)) /WHEEL_DIAMETER;
    chassisMotor.targetSpeed.w2 = -(Vy - Vx - W0 * (L1 + L2 - L0)) /WHEEL_DIAMETER;
    chassisMotor.targetSpeed.w3 = -(Vy + Vx - W0 * (L1 + L2 - L0)) /WHEEL_DIAMETER;
    chassisMotor.targetSpeed.w4 =  (Vy - Vx + W0 * (L1 + L2 - L0)) /WHEEL_DIAMETER;
}

int16_t chassisCurrentLimit(int16_t current){
    return current > MAX_CURRENT ? MAX_CURRENT : (current < -MAX_CURRENT ? -MAX_CURRENT : current);
}

/*
    @ author: ��֮��
    @ latest  update:2018��10��14��;
    @ function: �����Լ죬OK����1�����󷵻�0��main.c�е���
*/
int8_t chassisSelfCheck(void){
    delay_ms(3000);
    printf("%d,",connectionState.gimbalConnection);
    printf("%d,",connectionState.motor1Connection);
    printf("%d,",connectionState.motor2Connection);
    printf("%d,",connectionState.motor3Connection);
    printf("%d\r\n",connectionState.motor4Connection);
    if(connectionState.gimbalConnection!=0x01)
        return 0;
    if(connectionState.motor1Connection!=0x01)
        return 0;
    if(connectionState.motor2Connection!=0x01)
        return 0;
    if(connectionState.motor3Connection!=0x01)
        return 0;
    if(connectionState.motor4Connection!=0x01)
        return 0;
    return 1;
}
/******************************************************************
*************************�ӿڴ�����*********************************
******************************************************************/
//���õ��̵���ĵ���ֵ���������������˵����ľ���ֵ��С;
void setMotorCurrentIncrement(int16_t current1,int16_t current2,int16_t current3,int16_t current4){
    chassisMotor.current.c1 += current1;
    chassisMotor.current.c2 += current2;
    chassisMotor.current.c3 += current3;
    chassisMotor.current.c4 += current4;
    
    chassisMotor.current.c1 = chassisCurrentLimit(chassisMotor.current.c1);
    chassisMotor.current.c2 = chassisCurrentLimit(chassisMotor.current.c2);
    chassisMotor.current.c3 = chassisCurrentLimit(chassisMotor.current.c3);
    chassisMotor.current.c4 = chassisCurrentLimit(chassisMotor.current.c4);
}

//���ø���������趨�ٶ�ֵ;
void setTargetSpeed(int16_t speed1,int16_t speed2,int16_t speed3,int16_t speed4){
    chassisMotor.targetSpeed.w1 = speed1;
    chassisMotor.targetSpeed.w2 = speed2;
    chassisMotor.targetSpeed.w3 = speed3;
    chassisMotor.targetSpeed.w4 = speed4;
}

//�����������̵��˶�����;
void setMotorComponent(int16_t VX,int16_t VY,int16_t W0){
    chassisMotor.component.VX = VX;
    chassisMotor.component.VY = VY;
    chassisMotor.component.W0 = W0;
    speedSolving();
}

//��ȡ���̸�������ĵ�ǰת��ֵ;
int16_t getMotorVelocity(int num){
    switch(num){
        case 1: return chassisMotor.velocity.v1;break;
        case 2: return chassisMotor.velocity.v2;break;
        case 3: return chassisMotor.velocity.v3;break;
        case 4: return chassisMotor.velocity.v4;break;
    }
    return 0;
}

//��ȡ����������趨�ٶ�ֵ;
int16_t getMotorTargetSpeed(int num){
    switch(num){
        case 1: return chassisMotor.targetSpeed.w1;break;
        case 2: return chassisMotor.targetSpeed.w2;break;
        case 3: return chassisMotor.targetSpeed.w3;break;
        case 4: return chassisMotor.targetSpeed.w4;break;
    }
    return 0;
}


