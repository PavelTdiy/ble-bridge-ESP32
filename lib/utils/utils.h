/*
	My library with different useful functions,
*/

#include <string>

// if not used before - include Renesas lib to control GPAK from I2C
#include "Silego.h"
#include "macros/SLG46826.h"    // Include macros for SLG46531

// lib to control micro-servos using angle references
#include "Servo.h"

#ifndef utils_h
#define utils_h


class Utils {
  public:
    //class variables
    int Nruns;
    Silego GPAK{0x08, 19, 18};
    Servo firstServo{1};

    // constructor function
    Utils(int exNumber);
    
    // convert string to int for servos
    int strToInt(std::string strVal);

    //blink onboard led (IO02)
    void blink();

    //parse command from client to channel and values
    void executeCommand(std::string commandStr);

};

#endif

