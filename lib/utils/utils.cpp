#include "Arduino.h"
#include "utils.h"
#include <math.h>
// #include <String.h>
#include <string>

using namespace std;

Utils::Utils(int exNumber)
  : Nruns(1)
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

void Utils::parseCommand(std::string commandStr){
  printf("We are in parseCommand. Value:");
//   printf(commandStr);
//   Serial.println(commandStr);
//   return 0;
}