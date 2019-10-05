#include "WatchMyChicken.h"

  // Connected to L298N Motor Driver In1, In2, In3, In4 
  // Pins entered in sequence 1-2-3-4 for proper step sequencing
  Stepper stepperMotorFood(STEPPER_STEPS_PER_REV, STEPPER_MOTOR_IN1, STEPPER_MOTOR_IN2, STEPPER_MOTOR_IN3, STEPPER_MOTOR_IN4);
    
  WatchMyChicken::WatchMyChicken(){    
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


/*
 * 
 * All methods of step motor (which it feed the chickens)
 * 
 * 
 */
  
  bool WatchMyChicken::feedsTheChickens()
  {
    int numberOfSteps;

    numberOfSteps == 0 ? NUMBER_STEPS_DEFAULT : definedStepsByConfig;
    
    stepperMotorFood.setSpeed(STEPPER_SPEED);
    
    // step 1/100 of a revolution:
    stepperMotorFood.step(STEPPER_STEPS_PER_REV / 100 * numberOfSteps);

    return true;    
  }

  int WatchMyChicken::getActualConfigNumberOfStepsMotor()
  {
    return definedStepsByConfig == 0 ? NUMBER_STEPS_DEFAULT : definedStepsByConfig;
  }

  bool WatchMyChicken::increaseNumberOfSteps()
  {
    
    definedStepsByConfig = definedStepsByConfig + STEPPER_CONFIG_INTERVAL; 

    return true;
  }

  bool WatchMyChicken::decreaseNumberOfSteps()
  {
    
    definedStepsByConfig = definedStepsByConfig - STEPPER_CONFIG_INTERVAL; 

    return true;
  }

/*
 * 
 * All methods of photocell delta
 * 
 */

  bool WatchMyChicken::isNight()
  {
    int photocellReading = analogRead(PHOTOCELL_PIN_SENSOR);
    
    int photocellDeltaValue = photocellDefinedDelta != 0 ? photocellDefinedDelta : DEFAULT_PHOTOCELL_DELTA;

    Serial.print("Analog reading PHOTOCELL_PIN_SENSOR = ");
    Serial.println(photocellReading);

    Serial.print("photocellDeltaValue = ");
    Serial.println(photocellDeltaValue);

    return photocellReading < photocellDeltaValue ? true: false;
  }
  
  int WatchMyChicken::getPhotocellDelta()
  {
    return photocellDefinedDelta != 0 ? photocellDefinedDelta : DEFAULT_PHOTOCELL_DELTA;
  }

  bool WatchMyChicken::increasePhotocellDelta()
  {
    
    photocellDefinedDelta = photocellDefinedDelta + PHOTOCELL_CONFIG_INTERVAL; 

    return true;
  }

  bool WatchMyChicken::decreasePhotocellDelta()
  {
    
    photocellDefinedDelta = photocellDefinedDelta - PHOTOCELL_CONFIG_INTERVAL; 

    return true;
  }
 
  
