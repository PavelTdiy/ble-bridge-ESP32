/*
	My library with different useful functions,
*/

#include <string>


#ifndef utils_h
#define utils_h


class Utils {
  public:
    //class variables
    int Nruns;

    // constructor function
    Utils(int exNumber);
    
    // convert string to int for servos
    int strToInt(std::string strVal);

    //blink onboard led (IO02)
    void blink();

    //parse command from client to channel and values
    void parseCommand(std::string commandStr);

    //split string
    std::string split(std::string str, std::string del);

};

#endif

