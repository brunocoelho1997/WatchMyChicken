#ifndef WatchMyChicken_h
#define WatchMyChicken_h

#include "Arduino.h"

class WatchMyChicken
{
  public:
    WatchMyChicken();
    double getFoodTankState();
    double getWaterTankState();
    double getActualTemperature();
    
  private:
    double getFoodTankDistance();
    double getWaterTankDistance();
    double getTankDistance(int trigPinTank, int echoPinTank);
    
    
    //int privateVar; //a private var
    
};

#endif
