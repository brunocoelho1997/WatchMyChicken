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
    int getActualConfigNumberOfStepsMotor();
    bool increaseNumberOfSteps();
    bool decreaseNumberOfSteps();

    bool isNight();
    bool increasePhotocellDelta();
    bool decreasePhotocellDelta();
    int getPhotocellDelta();
    
    
  private:
    /*
     * private vars
     * 
     */
    
    //number of steps defined by user in his configuration
    int definedStepsByConfig;

    //delta used by photocell - if it isn't defined it will assume the default (DEFAULT_PHOTOCELL_DELTA) 
    int photocellDefinedDelta;
    
    
    /*
     * Private methods
     */
    double getFoodTankDistance();
    double getWaterTankDistance();
    double getTankDistance(int trigPinTank, int echoPinTank);

    
    
};

#endif
