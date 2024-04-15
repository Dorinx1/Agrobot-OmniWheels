#include <Arduino.h>
#include <stdint.h>
#include <Servo.h>

/*Private include*/
#include "CTRL_Steering/ctrl_steering.h"

/*Declare Structure*/
    typedef struct Angle_DG{               //Angle DeGree
    uint8_t Angle_0;
    uint8_t Angle_90;
    uint8_t Angle_180;
    }Angle;

/*Declare Variable*/
uint16_t Current_Power;
char cmd;
int8_t servoPin = 6;     
bool Left_Key_pressed = false;
bool Right_Key_pressed = false;
uint8_t CurrentAngle;
Angle P1 = {0,90,180};    



/*Declare servo variable*/
Servo myServo;                         // Servo type variable

/*void Setup()*/
void ctrl_steering_setup()
{
  pinMode(ENA,OUTPUT);
  myServo.attach(servoPin);             // Attach the servo to the pin
  // Serial.println("CTRL_STEERING_START\n");
  _Starting_Position_Stering();         //attach starting position to 90 degree for potentiometre 
}

/*void loop*/
void ctrl_steering_loop()
{
  cmd = Serial.read();
  Command(cmd);
}


/*Function*/
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



uint16_t Ctrl_SetValue_Power() 
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
    return Current_Power;   
  } 
  else return 1;
}

void Command(char cmd)
{
    switch(cmd)
    {
    case 'a':
      Serial.println("Typed 'a' -> motor moving Left\n");
      Left_Key_pressed = true;
      analogWrite(ENA, Ctrl_SetValue_Power());  
      _Stering_Left();  
      break;
    case 'd':
      Serial.println("Typed 'd' -> motor moving Right\n");
      Right_Key_pressed = true;
      analogWrite(ENA, Ctrl_SetValue_Power());
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
    case 'z':
      Ctrl_SetValue_Power();
      break;
    case 'c':
      Current_Power = 0;
      break;
    default:
      Serial.println("..........Unknown command..........");
      break;
    }
}

