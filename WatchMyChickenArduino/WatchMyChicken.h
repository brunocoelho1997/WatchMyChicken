#ifndef WatchMyChicken_h
#define WatchMyChicken_h

#include "Arduino.h"

class WatchMyChicken
{
  public:
    WatchMyChicken();
    double getFoodTankState();
    
  private:
    double getFoodTankDistance();
    double getSoundAirCalculedDistance(long duration);
    double getSoundWaterCalculedDistance(long duration);
    
    
    //int privateVar; //a private var
    
};

#endif
