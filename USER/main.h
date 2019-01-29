#ifndef __MAIN_H__
#define __MAIN_H__

#include "config.h"
#include "timer.h"
#include "visualscope.h"
#include "key.h"
#include "CAN.h"
#include "judge.h"

typedef enum {
    SELF_CHECK_STATE = 0x00,
    NORMAL_STATE     = 0x01
}CHASSIS_STATE_TYPE;

CHASSIS_STATE_TYPE getChassisState(void);
#endif
