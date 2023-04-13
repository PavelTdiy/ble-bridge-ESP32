/*
	Servo - class to control up to 4 servos,
    connected to GPAK through I2C
*/

// ensure this library description is only included once
#ifndef Servo_h
#define Servo_h

// if not used before - include Renesas lib to control GPAK from I2C
#include "Silego.h"
#include "macros/SLG46826.h"    // Include macros for SLG46531

class Servo {
	public:
        // class variables
        int MaxAngles[4]; //joint max angles
        int adr; // GPAK I2C address
        int AddressesServo[4];
        int Ndevices;
        Silego silego{0x08, 19, 18};

		Servo(int Number);
		
		// Set joints servo to given angle
		void setDegServo(int deg, int joint);

        // Set joints servo to given angle in string
		void setDegStrServo(std::string degStr, int joint);

        // Set joints in given positions
		void setPosition(int angles[10]);
};


#endif

