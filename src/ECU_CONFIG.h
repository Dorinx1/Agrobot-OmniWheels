#ifndef ECU_CONFIG_H_
#define ECU_CONFIG_H_

/*Electronic Config Unit*/

/*Define ECU Config*/
#define ECU_CONFIG

/*Define ECU Dispositive*/
#define USE_CAN_SETUP
#define USE_STERING_SETUP

#elif ECU_CONFIG == USE_CAN_SETUP
#include "DD_CAN_MCP/dd_can_mcp.h"

#elif ECU_CONFIG == USE_STERING_SETUP
#include "DD_STERING/dd_stering.h"
#endif


#endif