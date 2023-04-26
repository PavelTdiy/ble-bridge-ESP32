#include "Arduino.h"
#include "Servo.h"
#include <math.h>
#include <String.h>
#include <string>

using namespace std;

// if not used before - include Renesas lib to control GPAK from I2C
// #include "Silego.h"
// #include "macros/SLG46826.h"    // Include macros for SLG46531

Servo::Servo(int Number)
  : MaxAngles {90, 90, 90, 90}//joint max angles
  , AddressesServo {CNT2_DATA, CNT3_DATA, CNT4_DATA, CNT5_DATA}// servo counter data addresses
  , Ndevices (Number)
  , adr(0x08)
{
}

// Using GPAK controlled via I2C
void Servo::setDegServo(int deg, int joint) {
  int delayCounterData = round(255*deg/MaxAngles[joint]);
  if (delayCounterData <= 0) {delayCounterData = 1;};
  if (delayCounterData > 255) {delayCounterData = 255;};
  Serial.print("Set servo ");
  Serial.print(deg);
  Serial.print(u8"° = ");
  Serial.print(delayCounterData);
  Serial.println(" to DLY");
  silego.writeI2C(AddressesServo[joint], delayCounterData);
}

void Servo::setDegStrServo(std::string degStr, int joint){
  //FIXME: use strToInt from services
  setDegServo(strToInt(degStr), 0);
}

int Servo::strToInt(std::string strVal) {
  int n = 0;
  for (int i = strVal.size(); i --> 0;) {
    char c = strVal[i];
    int pw = strVal.size() - 1 - i;
    if (c >= 48 && c <= 57) {
      n += (c - 48) * pow(10, pw);
    }
    else {
      printf("Bad Input. Ignored");
      return 0;
    }
  }
  return n;
}

void Servo::setPosition(int angles[4]) {
  size_t length = sizeof(angles);
  for (int i = 0; i < length; i++){
    setDegServo(angles[i],i);
  };
}
