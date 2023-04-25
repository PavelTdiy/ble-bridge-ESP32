/*
	My library with different useful functions,
*/

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

    //parse command from client to channel and values
    void parseCommand(std::string commandStr);

};

#endif

