#ifndef _DD_STERING_H_
#define _DD_STERING_H_

/*Include define*/
#define ENA 5 

/*Declare Function*/
void dd_stering_setup();
void dd_stering_loop();
void _ENA_Interupts();
void _Starting_Position_Stering();
uint8_t _Stering_Left();
uint8_t _Stering_Right();
void Comand_Relise(char cmd);

#endif