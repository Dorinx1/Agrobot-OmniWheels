#ifndef ECU_CONFIG_H_
#define ECU_CONFIG_H_

/*Electronic Config Unit*/

/*Define ECU Config*/
#define ECU_CONFIG

/*Define ECU Dispositive*/
#define USE_DD_CAN_SETUP
#define USE_CTRL_STEERING_SETUP

#elif ECU_CONFIG == USE_DD_CAN_SETUP
#include "DD_CAN_MCP/dd_can_mcp.h"

#elif ECU_CONFIG == USE_CTRL_STEERING_SETUP
#include "CTRL_Steering/ctrl_steering.h"
#endif

#endif