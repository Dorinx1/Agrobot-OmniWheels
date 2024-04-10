#include <Arduino.h>

/*Private include*/
#include "CTRL_Steering/ctrl_steering.h"
#include <stdint.h>

/*Declare Variable*/
uint16_t Current_Power;
char cmd;

/*void Setup()*/

void ctrl_steering_setup()
{
  
}

/*void loop*/
void ctrl_steering_loop()
{
  cmd = Serial.read();
  Command(cmd);
}


/*Function*/
uint16_t Ctrl_get_MaxPower()
{
    /*Take Power from Define to
    not work with Global Variable*/
    uint16_t Max_Power = MaxPower;
    return Max_Power;
}

uint16_t Ctrl_get_MinPower()
{
    uint16_t Min_Power = MinPower;
    return Min_Power;
}


uint8_t _convert_value(uint8_t num)
{    
   /*Convert the 8 bit value in 
    (0 - 100) % */
   num = map(num,Ctrl_get_MinPower(),Ctrl_get_MaxPower(),0,100);

   return num;
}

void Ctrl_Up_Date_Power()
{
    // Serial.println("Update Power:");
    // Current_Power = 0;
    // Current_Power = Ctrl_SetValue_Power(); 
    // Serial.print("Power = "); 
    // Serial.println(Current_Power);
}


void Ctrl_SetValue_Power() 
{
  Serial.print("Include Power: ");
  Serial.println();
  while (!Serial.available()) {
  }
 
  Current_Power = _convert_value(Current_Power);
  Current_Power = Serial.parseInt();
 
  if (Current_Power >= 0 && Current_Power <= 100) 
  {
    Serial.print("Power = "); 
    Serial.println(Current_Power);
  } else {
    Serial.println("Puterea introdusa nu este intre 0 si 100.");
  }
}

void Command(char cmd)
{
    switch(cmd)
    {
      case 'z':
      Ctrl_SetValue_Power();
      break;

      case 'x':
      Ctrl_Up_Date_Power();
      break;

      case 'c':
      Current_Power = 0;
      break;

      default:
      Serial.println("Comanda necunoscuta.");
      break;
    }
}

