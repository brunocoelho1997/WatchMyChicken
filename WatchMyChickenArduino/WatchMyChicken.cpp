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
    double distance = getTankDistance(TRIG_PIN_FOOD_TANK, ECHO_PIN_FOOD_TANK);

    //it's necessary apply more calculus

    return distance;
  }

  /*
  * Get the actual state of the water tank (0 - 100%)
  */
  double WatchMyChicken::getWaterTankState()
  {
    double distance = getTankDistance(TRIG_PIN_WATER_TANK, ECHO_PIN_WATER_TANK);

    //it's necessary apply more calculus

    return distance;
  }

  double WatchMyChicken::getTankDistance(int trigPinTank, int echoPinTank)
  {
    // Clears the trigPin
    digitalWrite(trigPinTank, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPinTank, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinTank, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(echoPinTank, HIGH);

    return duration*SOUND_AIR_SPEED/2;
  }

  double WatchMyChicken::getActualTemperature()
  {
    int value=analogRead(TEMPERATURE_PIN_SENSOR);
    double volts=(value/1024.0)*5.0;
    double temperature = volts*100.0;

    return temperature;
  }
  
