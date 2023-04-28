/*
	My library with different useful functions,
*/

#include <string>

// if not used before - include Renesas lib to control GPAK from I2C
#include "Silego.h"
#include "macros/SLG46826.h"    // Include macros for SLG46826

// lib to control micro-servos using angle references
#include "Servo.h"

#ifndef services_h
#define services_h


class Services {
  public:
    //class variables
    int Nruns;
    Silego GPAK{0x08, 19, 18};
    Silego HVPAK{0x10, 19, 18};
    Servo servo{1};

    // constructor function
    Services(int exNumber);
    
    // convert string to int for servos
    int strToInt(std::string strVal);

    //blink onboard led (IO02)
    void blink();

    //parse command from client to channel and values
    uint8_t executeCommand(std::string commandStr);

};

#endif

