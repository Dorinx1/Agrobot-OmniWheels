#ifndef CTRL_STEERING_H_
#define CTRL_STEERING_H_

/*Private define*/
#define MaxPower 255
#define MinPower 0

/*Define function*/

void ctrl_steering_setup();
void ctrl_steering_loop();

uint16_t Ctrl_get_MaxPower();
uint16_t Ctrl_get_MinPower();
uint8_t _convert_value(uint8_t num);
void Ctrl_Up_Date_Power();
void Ctrl_SetValue_Power() ;
void Command(char cmd);

#endif