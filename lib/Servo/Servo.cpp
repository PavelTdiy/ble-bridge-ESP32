

#include "Arduino.h"
#include "Servo.h"
#include <math.h>

// if not used before - include Renesas lib to control GPAK from I2C
// #include "Silego.h"
// #include "macros/SLG46826.h"    // Include macros for SLG46531

Servo::Servo(int Number)
  : MaxAngles {90, 90, 90, 90}//joint max angles
  , AddressesServo {0xAF, 0xB3, 0xB8, 0xBC}// servo counter data addresses
  , Ndevices (Number)
  , adr(0x08)
{
}

// Using GPAK controlled via I2C
void Servo::setDegServo(int deg, int joint) {
  int delayCounterData = round(255*deg/MaxAngles[joint]);
  if (delayCounterData <= 0) {delayCounterData = 1;};
  if (delayCounterData > 255) {delayCounterData = 255;};
  Serial.printf("Sending to servo ");
  Serial.println(delayCounterData);
  silego.writeI2C(0xAF, delayCounterData);
}

void Servo::setPosition(int angles[10]) {
  for (int i = 0; i < sizeof(angles); i++){
    setDegServo(angles[i],i);
  };
}
