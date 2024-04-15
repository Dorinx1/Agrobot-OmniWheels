#include <Arduino.h>
#include <stdint.h>

/*Private include (library) */
#include "DD_CAN_MCP/dd_can_mcp.h"
#include "CTRL_Steering/ctrl_steering.h"

 
/*Private define*/
#define SYS_TICK 1

#define CAN_SEND_REC (1000 / SYS_TICK)
#define CAN_RECV_REC (1 / SYS_TICK)
#define CAN_PRINT_REC (2000/SYS_TICK)  //is not used
#define CTRL_STEERING_REC (10 / SYS_TICK)

/*Private variable*/
int16_t send_rec_cnt = CAN_SEND_REC;
int8_t recv_rec_cnt = CAN_RECV_REC;
int16_t print_rec_cnt = CAN_PRINT_REC;
int16_t ctrl_steering_cnt = CTRL_STEERING_REC;

/*Declare Setup*/
void setup() 
{
  /*Initialization Serial begin just one time*/
  Serial.begin(9600);

  #ifdef USE_CAN_SETUP
  dd_can_setup(); 
  #endif

  #ifdef USE_CTRL_STEERING_SETUP
  ctrl_steering_setup();
  #endif
}

/*Enter in loop*/
void loop()
{
   if (--send_rec_cnt <= 0)            // algorit to transmite data pe  ( X )ms 
  {// send data per 50ms
    dd_can_send_loop();
    send_rec_cnt = CAN_SEND_REC;
  }

  if (--recv_rec_cnt <= 0)
  { // receive data per 0,01 ms
    dd_can_recv_loop();
    recv_rec_cnt = CAN_RECV_REC;
  }

  if (--ctrl_steering_cnt <= 0)  
  {
    ctrl_steering_loop();
    ctrl_steering_cnt = CTRL_STEERING_REC;
  }

}  

