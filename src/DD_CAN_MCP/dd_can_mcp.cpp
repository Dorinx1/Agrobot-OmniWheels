#include "Arduino.h"
#include <mcp_can.h>
#include "dd_can_mcp.h"

#define CAN_MESSAGE_LEN 8

long unsigned int rxId;
unsigned char len = 0;
uint8_t dd_can_rx_data[CAN_MESSAGE_LEN];
uint8_t dd_can_tx_data[CAN_MESSAGE_LEN] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

char msgString[128]; // Array to store serial string

MCP_CAN CAN0(CAN0_CS); // Set CS to pin 10

//=============================================================
// Can Setup
void dd_can_setup()
{
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
  // Change to normal mode to allow messages to be transmitted
  CAN0.setMode(MCP_NORMAL);
  // Configuring pin for /INT input (optional)
  pinMode(CAN0_INT, INPUT);

  Serial.println("MCP2515 Driver started...");
}

//=============================================================
// Receiving Process
void dd_can_recv_loop()
{
  // Check if data is received
  if (CAN_MSGAVAIL == CAN0.checkReceive())
  // if (!digitalRead(CAN0_INT)) // If CAN0_INT pin is low, read receive buffer
  {
    // Read data: len = data length, buf = data byte(s)
    CAN0.readMsgBuf(&rxId, &len, dd_can_rx_data);
    // Determine if ID is standard (11 bits) or extended (29 bits)
    // if ((rxId & 0x80000000) == 0x80000000)
    //   sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    // else
    //   sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
    // Serial.print(msgString);

    // // Determine if message is a remote request frame.
    // if ((rxId & 0x40000000) == 0x40000000)
    // {
    //   // sprintf(msgString, " REMOTE REQUEST FRAME");
    //   // Serial.print(msgString);
    // }
    // else
    // {
    //   // for (byte i = 0; i < len; i++)
    //   // {
    //   //   sprintf(msgString, " 0x%.2X", dd_can_rx_data[i]);
    //   //   Serial.print(msgString);
    //   // }
    //   // Serial.println(rxId);

    //   // dd_can_matrix_set(rxId, dd_can_rx_data, len);
    // }
  }
}

//=============================================================
// Sending Process
void dd_can_send_loop()
{
  // send data to the CAN network
  byte sndStat = CAN0.sendMsgBuf(MY_CAN_ID, // ID = 0x128,
                                 0,         // Standard CAN Frame,
                                 8,         // Data length = 8 bytes,
                                 dd_can_tx_data);     // 'data' = array of data bytes to send
  // Check the status for sending
  if (sndStat == CAN_OK)
  {
    Serial.println("Message Sent Successfully!");
  }
  else
  {
    Serial.println("Error Sending Message...");
  }
}