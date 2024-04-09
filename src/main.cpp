#include <Arduino.h>
#include <stdint.h>

/*Private include (library) */
#include "DD_CAN_MCP/dd_can_mcp.h"
#include "DD_STERING/dd_stering.h"

/*Private define*/
#define SYS_TICK 1

#define CAN_SEND_REC (5000 / SYS_TICK)
#define CAN_RECV_REC (1 / SYS_TICK)
#define CAN_PRINT_REC (2000/SYS_TICK)  //is not used
#define STERING_PRINT_REC (100/SYS_TICK)

/*Private variable*/
int16_t send_rec_cnt = CAN_SEND_REC;
int8_t recv_rec_cnt = CAN_RECV_REC;
int16_t print_rec_cnt = CAN_PRINT_REC;
int32_t stering_rec_cnt = STERING_PRINT_REC;

/*Declare Setup*/
void setup() 
{
  /*Initialization Serial begin just one time*/
  Serial.begin(9600);

  #ifdef USE_CAN_SETUP
  dd_can_setup(); 
  #endif

  #ifdef USE_STERING_SETUP
  dd__stering_setup(); 
  #endif


}

/*Enter in loop*/
void loop()
{
   if (--send_rec_cnt <= 0 )            // algorit to transmite data pe  ( X )ms 
  {// send data per 50ms
    dd_can_send_loop();
    send_rec_cnt = CAN_SEND_REC;
  }

  if (--recv_rec_cnt <= 0)
  { // Send data per 0,01 ms
    dd_can_recv_loop();
    recv_rec_cnt = CAN_RECV_REC;
  }

  if (--stering_rec_cnt <=0)
  {// send data per 0,10 ms
    dd_stering_loop();
    stering_rec_cnt = STERING_PRINT_REC;
  }

}  

