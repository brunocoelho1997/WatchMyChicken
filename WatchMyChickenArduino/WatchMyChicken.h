#ifndef WatchMyChicken_h
#define WatchMyChicken_h

#include "Arduino.h"
#include "Utils.h"
#include <Stepper.h>

class WatchMyChicken
{
  
  public:
    WatchMyChicken();
    double getFoodTankState();
    double getWaterTankState();
    double getActualTemperature();
    bool feedsTheChickens();
    
  private:
    /*
     * private vars
     * 
     */
    
    //number of steps defined by user in his configuration
    int definedStepsByConfig;
    
    /*
     * Private methods
     */
    double getFoodTankDistance();
    double getWaterTankDistance();
    double getTankDistance(int trigPinTank, int echoPinTank);
    

    
    
};

#endif
