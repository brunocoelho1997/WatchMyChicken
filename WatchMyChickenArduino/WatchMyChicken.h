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

    bool openTheWater();
    int getTheNumberOfSecondsOpenedWater();
    bool increaseWaterNumberOfMilliseconds();
    bool decreaseWaterNumberOfMilliseconds();
    
    bool calibrateSetMaximumWaterTank();
    bool calibrateSetMaximumFoodTank();
    bool verifyMinimunFood();
    bool verifyMinimunWater();

    int getTheNumberOfSecondsOpenCloseGate();
    bool increaseGateNumberOfMilliseconds();
    bool decreaseGateNumberOfMilliseconds();
    bool openTheGate();
    bool closeTheGate();
    bool isGateOpen();
    
        
  private:
    /*
     * private vars
     * 
     */

    double maximumDistanceWaterTank;

    double maximumDistanceFoodTank;
    
    //number of steps defined by user in his configuration
    int definedStepsByConfig;
    int feedMilliSecondsConfig;

    //delta used by photocell - if it isn't defined it will assume the default (DEFAULT_PHOTOCELL_DELTA) 
    int photocellDefinedDelta;

    //number of seconds that the water will be open
    int openedWaterMilliSecondsConfig;


    bool isGateClosed;
    //number of seconds that the motor of the gate will work to open and close
    int gateMilliSecondsConfig;
    
    
    /*
     * Private methods
     */
    double getFoodTankDistance();
    double getWaterTankDistance();
    double getTankDistance(int trigPinTank, int echoPinTank);
    bool verifyMinimumTankState(double actualState, int ledPinToBlink);
    
    
};

#endif
