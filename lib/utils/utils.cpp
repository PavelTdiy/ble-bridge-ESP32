#include "Arduino.h"
#include "utils.h"
#include <math.h>
// #include <String.h>
#include <iostream>
#include <string>

using namespace std;

Utils::Utils(int exNumber)
  : Nruns(0)
{
    Nruns++;
}

int Utils::strToInt(std::string strVal) {
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

void Utils::blink(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}

void Utils::parseCommand(string commandStr){
  printf("%s\n", commandStr.c_str());
  std::string delim = ": ";
  std::size_t found = commandStr.find(delim);
  if (found!=std::string::npos){
    std::string commandVal = commandStr.substr(found + delim.length());
    std::string commandKey = commandStr.erase(found, commandStr.length() - 1);
    // printf("%s\n", commandVal.c_str());
    // printf("%s\n", commandKey.c_str());
    if (commandKey.compare("servo") == 0) {
      printf("Servo command detected - ");
      printf("%s\n", commandVal.c_str());
      // myServo.setDegStrServo(rxValue, 0);
    }
    else if (commandKey.compare("virtual") == 0) {
      printf("Virtual OUTs change - ");
      printf("%s\n", commandVal.c_str());
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

std::string Utils::split(std::string str, std::string del){
//     // declaring temp string to store the curr "word" upto del
  int end = str.find(del); 
  std::string keyName = str.substr(end);
  printf("%s\n", keyName);
  return keyName;
}
