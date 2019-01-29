#include "key.h"

uint8_t rowLine=0XFF,colLine=0XFF;  //hΪ���� lΪ����
uint8_t press=0xFF;
int key=0;
int m,keyUp;

int checkKey(void){
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOA,ENABLE);

    /*�����������*/
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    /*������������*/
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_10;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    /*�����������ȫΪ0*/
    GPIO_WriteBit(GPIOB, GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3, Bit_RESET);
    GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);
    delay_us(1);

    /*��ȡ���������ƽ*/
    colLine&=(uint8_t)((GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11)<<0)|
				 (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_10)<<1)|
				 (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)<<2)|
				 (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)<<3));
    if(colLine!=0X0F){
        delay_ms(10);       //��ʱȥ��
        colLine&=(uint8_t)( (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11)<<0)|
                            (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_10)<<1)|
                            (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)<<2) |
                            (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)<<3));
        if(colLine!=0X0F){
            /* �����߽��� */
            keyUp=1;//��������
            /*�����������*/
            GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
            GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;

            GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_10;
            GPIO_Init(GPIOC,&GPIO_InitStructure);

            GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
            GPIO_Init(GPIOA,&GPIO_InitStructure);
			
            GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
            GPIO_Init(GPIOB,&GPIO_InitStructure);

            /*������������*/                   
            GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
            GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;

            GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3;
            GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
            GPIO_Init(GPIOB,&GPIO_InitStructure);

            GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
            GPIO_Init(GPIOC,&GPIO_InitStructure);

            /* �����������Ϊ0 */
            GPIO_WriteBit(GPIOC, GPIO_Pin_11|GPIO_Pin_10, Bit_RESET);
            GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_RESET);
            GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_RESET);
            delay_ms(2);
            /*��ȡ���������ƽ*/
            rowLine&=(uint8_t)((GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)<<3)| 
                               (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)<<2)|
                               (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)<<1)|
                               (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12)<<0));

            press=(rowLine<<4|colLine); 
        }
        switch(press){
            case 0xee: m = 1; break;
            case 0xed: m = 2; break;
            case 0xeb: m = 3; break;
            case 0xe7: m = 4; break;
            case 0xde: m = 5; break;
            case 0xdd: m = 6; break;				
            case 0xdb: m = 7; break;
            case 0xd7: m = 8; break;
            case 0xbe: m = 9; break;
            case 0xbd: m = 10; break;
            case 0xbb: m = 11; break;
            case 0xb7: m = 12; break;
            case 0x7e: m = 13; break;
            case 0x7d: m = 14; break;
            case 0x7b: m = 15; break;
            case 0x77: m = 16; break;
        }
    }
    if((colLine == 0X0F) && (keyUp == 1)){
        keyUp = 0;//�����ɿ�
        key = m;
        m = 0;
    }   
    return key;
}

void calcPID(void){
    switch(checkKey()){
        case 1:
            break;
        case 2:
            break;
        case 3:
            setPIDParamChange(CHASSIS_PID_3,0.01,0,0);
            break;
        case 4:
            setPIDParamChange(CHASSIS_PID_3,-0.01,0,0);
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            setPIDParamChange(CHASSIS_PID_3,0,0.01,0);
            break;
        case 8:
            setPIDParamChange(CHASSIS_PID_3,0,-0.01,0);
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            setPIDParamChange(CHASSIS_PID_3,0,0,0.01);
            break;
        case 12:
            setPIDParamChange(CHASSIS_PID_3,0,0,-0.01);
            break;
        case 13:
            break;
        case 14:
            break;
        case 15:
            break;
        case 16:
            break;
    }					
}


