#include "WatchMyChicken.h"
#include "Utils.h"

  WatchMyChicken::WatchMyChicken(){
    //privateVar = 0;
  }

  /*
  * Get the actual state of the food tank (0 - 100%)
  */
  double WatchMyChicken::getFoodTankState()
  {
    return getFoodTankDistance();
  }

  
  double WatchMyChicken::getFoodTankDistance()
  {
    // Clears the trigPin
    digitalWrite(trigPinFoodTank, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPinFoodTank, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinFoodTank, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(echoPinFoodTank, HIGH);

    return getSoundAirCalculedDistance(duration);
  }


  double WatchMyChicken::getSoundAirCalculedDistance(long duration)
  {
    return duration*SOUND_AIR_SPEED/2;
  }

  double WatchMyChicken::getSoundWaterCalculedDistance(long duration)
  {
    return duration*SOUND_AIR_SPEED/2;
  }

  
