#ifndef DD_MCP_CAN_H_
#define DD_MCP_CAN_H_

#define MY_CAN_ID 0x128         // Set ID
#define CAN0_INT 2              // Set INT to pin 2
#define CAN0_CS 10              // Set CS to pin 10

void dd_can_setup();            //Declare Setup
void dd_can_recv_loop();        //Declare receive loop
void dd_can_send_loop();        //Declare Send Message loop

#endif