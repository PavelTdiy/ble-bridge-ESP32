#include "Arduino.h"
#include "services.h"
#include <math.h>
#include <iostream>
#include <string>

using namespace std;

Services::Services(int exNumber)
  : Nruns(0)
{
    Nruns++;
}

int Services::strToInt(std::string strVal) {
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

void Services::blink(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}

void Services::executeCommand(string commandStr){
  // printf("%s\n", commandStr.c_str());
  std::string delim = ": ";
  std::size_t found = commandStr.find(delim);
  if (found!=std::string::npos){
    std::string commandVal = commandStr.substr(found + delim.length());
    std::string commandKey = commandStr.erase(found, commandStr.length() - 1);
    if (commandKey.compare("servo") == 0) {
      printf("Servo command detected - ");
      printf("%s\n", commandVal.c_str());
      servo.setDegStrServo(commandVal, 0);
    }
    else if (commandKey.compare("virtual") == 0) {
      printf("Virtual OUTs change - ");
      printf("%s\n", commandVal.c_str());
      GPAK.writeI2C(VIRTUAL_INPUTS, strToInt(commandVal));
    }
    else if (commandKey.compare("regw") == 0) {
      printf("Writing to register - ");
      std::string comma = ",";
      std::size_t pos = commandVal.find(comma);
      if (pos!=std::string::npos){
        std::string data = commandVal.substr(pos + 1);
        std::string addr = commandVal.erase(pos, commandVal.length() - 1);
        printf("%s\n", addr.c_str());
        printf("%s\n", data.c_str());
        GPAK.writeI2C(strToInt(addr), strToInt(data));
      }
      else {
        printf("Wrong register data or address format");
      }
    }
    else if (commandKey.compare("regr") == 0) {
      printf("Reading register - ");
      printf("%s\n", commandVal.c_str());
      uint8_t readedData = GPAK.readI2C(strToInt(commandVal));
      printf("%s\n", to_string(readedData).c_str());
    }
    else {
      printf("Absent command name");
    }
  }
  else {
    printf("Bad Command format");
  }
//   return 0;
}
