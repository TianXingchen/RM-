#ifndef __CAN_H__
#define __CAN_H__

#include "config.h"

void CAN1Init(void);
void CANSendData8(uint32_t stdId,int16_t data1,int16_t data2,int16_t data3,int16_t data4);

#endif
