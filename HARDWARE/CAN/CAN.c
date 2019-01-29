#include "CAN.h"

/**********************************************************************
*功能：Can1的初始化函数
***********************************************************************/
void CAN1Init(void){
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    GPIO_InitTypeDef       GPIO_InitStructure;
    NVIC_InitTypeDef       NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);//复用功能
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_TX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
    
    CAN_DeInit(CAN1);
    CAN_StructInit(&CAN_InitStructure);
    
    CAN_InitStructure.CAN_TTCM = DISABLE;//非时间触发通信模式
    CAN_InitStructure.CAN_ABOM = DISABLE;//软件自动离线管理
    CAN_InitStructure.CAN_AWUM = DISABLE;//睡眠模式通过软件唤醒（清除CAN->MCR的SLEEP位)
    CAN_InitStructure.CAN_NART = DISABLE;//CAN 硬件将自动重发送消息，直到根据 CAN 标准消息发送成功
    CAN_InitStructure.CAN_RFLM = DISABLE;//FIFO报文不锁定，满后新的覆盖旧的
    CAN_InitStructure.CAN_TXFP = ENABLE;//优先级由请求顺序（时间顺序）确定
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
    CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;
    CAN_InitStructure.CAN_Prescaler = 3;   //CAN BaudRate 42/(1+9+4)/3=1Mbps
    CAN_Init(CAN1, &CAN_InitStructure);

    CAN_FilterInitStructure.CAN_FilterNumber = 0;//过滤器0
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;//32位
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;//32位ID
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;//32位MASK
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;//过滤器0关联到FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;//激活过滤器0
    CAN_FilterInit(&CAN_FilterInitStructure);
    
    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//FIFO0收到消息中断允许		   
    CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);//发送邮箱为空中断 
}

void CANSendData8(uint32_t stdId,int16_t data1,int16_t data2,int16_t data3,int16_t data4){
    CanTxMsg TxMessage;
    TxMessage.StdId = stdId;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.IDE = CAN_Id_Standard;
    TxMessage.DLC = 8;

    TxMessage.Data[0] = data1 >> 8;
    TxMessage.Data[1] = data1 & 0xff;
	
    TxMessage.Data[2] = data2 >> 8;
    TxMessage.Data[3] = data2 & 0xff;
	
    TxMessage.Data[4] = data3 >> 8;
    TxMessage.Data[5] = data3 & 0xff;
	
    TxMessage.Data[6] = data4 >> 8;
    TxMessage.Data[7] = data4 & 0xff;

    CAN_Transmit(CAN1, &TxMessage);
}
