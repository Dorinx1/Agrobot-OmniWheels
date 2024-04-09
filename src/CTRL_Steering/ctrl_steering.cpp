#include <Arduino.h>

/*Private include*/
#include "CTRL_Steering/ctrl_steering.h"
#include <stdint.h>

/*Declare Variable*/
uint16_t Current_Power;

/*Function*/
uint16_t Ctrl_get_Power()
{
    /*Take Power from Define to
    not work with Global Variable*/
    uint16_t Max_Power = MaxPower;
    return Max_Power;
}

uint16_t Ctrl_Maping_Power()
{
    /*Convert the 8 bit value in 
    (0 - 100) % */
    uint16_t val = Ctrl_get_Power();
    uint16_t Maping_Power = map(val,0,255,0,100);
    return Maping_Power;
}

void Ctrl_Seting_Power()
{
    char string[100]

}

void ctr_include_willing_power()
{
    
}

