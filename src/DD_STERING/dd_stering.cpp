#include <Arduino.h>
#include <stdint.h>
#include <Servo.h>

/*Private incldue*/
#include "dd_stering.h"

/*Define include*/
int8_t servoPin = 6;     

/*Declare structure*/
    typedef struct Angle_DG{               //Angle DeGree
    uint8_t Angle_0;
    uint8_t Angle_90;
    uint8_t Angle_180;
    }Angle;

/*Declare Variable*/
char command;
uint8_t CurrentAngle;
bool Left_Key_pressed = false;
bool Right_Key_pressed = false;
Angle P1 = {0,90,180};    

/*Declare servo variable*/
Servo myServo;                         // Servo type variable

/*Write Function*/
void dd_stering_setup() {
  pinMode(ENA,OUTPUT);

  myServo.attach(servoPin);             // Attach the servo to the pin
  Serial.println("Start Program\n");
  _Starting_Position_Stering();         //attach starting position to 90 degree for potentiometre 
}

void dd_stering_loop()
{
  command = Serial.read(); // Citeste caracterul de la portul serial

  Comand_Relise(command);
}

void _ENA_Interupts()
{
  digitalWrite(ENA,LOW);
}

void _Starting_Position_Stering()
{
  analogWrite(ENA,100);
  myServo.write(P1.Angle_90);
  CurrentAngle = P1.Angle_90;
  delay(200);
}


uint8_t _Stering_Left() {
  if (CurrentAngle > 0) {
    myServo.write(--CurrentAngle);
    Serial.print("Left Angle -> ");
    Serial.println(CurrentAngle);
  }
  return CurrentAngle;
}


uint8_t _Stering_Right() {
  if (CurrentAngle < 180) {
    myServo.write(++CurrentAngle);
    Serial.print("Right Angle -> ");
    Serial.println(CurrentAngle);
  }
  return CurrentAngle;
}

// To make one muviong in one tact i use switch
void Comand_Relise(char cmd)
{
  switch (cmd) {
    case 'a':
      Serial.println("Typed 'a' -> motor moving Left\n");
      Left_Key_pressed = true;
      analogWrite(ENA, 100);  
      _Stering_Left();  
      break;
    case 'd':
      Serial.println("Typed 'd' -> motor moving Right\n");
      Right_Key_pressed = true;
      analogWrite(ENA, 100);
      _Stering_Right();  
      break;
    case 'r':
      Serial.println("Starting Position is Seting  - 90 DeGree");
      _Starting_Position_Stering();
      break;
    case 's':
      Serial.println("Typed 's' -> stopping motor\n");
      _ENA_Interupts();
      break;
    default:
      // Dacă s-a introdus o comandă necunoscută
      Serial.println("Unknown command");
      break;
  }
}
