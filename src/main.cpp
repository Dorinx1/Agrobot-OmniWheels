#include <Arduino.h>
#include <stdint.h>

/*Private include (library) */
#include "DD_CAN_MCP/dd_can_mcp.h"
#include "DD_STERING/dd_stering.h"

/*Private define*/
#define SYS_TICK 1

#define CAN_SEND_REC (5000 / SYS_TICK)
#define CAN_RECV_REC (1 / SYS_TICK)
#define CAN_PRINT_REC (2000/SYS_TICK)

/*Private variable*/
int16_t send_rec_cnt = CAN_SEND_REC;
int8_t recv_rec_cnt = CAN_RECV_REC;
int16_t print_rec_cnt = CAN_PRINT_REC;

/*Declare Setup*/
void setup() 
{
  Serial.begin(9600);
  dd_can_setup(); 
}

/*Enter in loop*/
void loop()
{
   if (--send_rec_cnt <= 0 )            // algorit to transmite data pe  ( X )ms 
  {// send data per 500ms
    dd_can_send_loop();
    send_rec_cnt = CAN_SEND_REC;
  }
  if (--recv_rec_cnt <= 0)
  { // Send data per 1 ms
    dd_can_recv_loop();
    recv_rec_cnt = CAN_RECV_REC;
  }
}  

