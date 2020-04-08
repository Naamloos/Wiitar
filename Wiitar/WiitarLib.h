#include <Arduino.h>

class Guitar
{
  public:
    // fields
    int WhammyBar = 0;
    int Plus = 0;
    int Minus = 0;
    int StrumUp = 0;
    int StrumDown = 0;
    int Green = 0;
    int Red = 0;
    int Yellow = 0;
    int Blue = 0;
    int Orange = 0;
    int Joy_X = 0;
    int Joy_Y = 0;

    // constructor
    void initialize();

    // update method
    void update();
};
