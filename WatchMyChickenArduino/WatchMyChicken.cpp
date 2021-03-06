#include "WatchMyChicken.h"

  // Connected to L298N Motor Driver In1, In2, In3, In4 
  // Pins entered in sequence 1-2-3-4 for proper step sequencing
  Stepper stepperMotorFood(STEPPER_STEPS_PER_REV, STEPPER_MOTOR_IN1, STEPPER_MOTOR_IN2, STEPPER_MOTOR_IN3, STEPPER_MOTOR_IN4);
    
  WatchMyChicken::WatchMyChicken(){    
//    isGateClosedVar = true;

  }
  
  /*
  * Get the actual state of the food tank (0 - 100%)
  */
  double WatchMyChicken::getFoodTankState()
  {
    double actualDistance = getTankDistance(TRIG_PIN_FOOD_TANK, ECHO_PIN_FOOD_TANK);

    if(maximumDistanceFoodTank == 0)
      return -1;

    return 100 - ((actualDistance * 100 ) / maximumDistanceFoodTank);
  }
  
  boolean WatchMyChicken::calibrateSetMaximumFoodTank()
  {
    maximumDistanceFoodTank = getTankDistance(TRIG_PIN_FOOD_TANK, ECHO_PIN_FOOD_TANK);
    return true;
  }

  boolean WatchMyChicken::verifyMinimunFood()
  {
    double actualDistance = getFoodTankState();

    return verifyMinimumTankState(actualDistance, LED_PIN_LOW_FOOD_AND_WATER);
  }

  

  
  
  /*
  * Get the actual state of the water tank (0 - 100%)
  */
  double WatchMyChicken::getWaterTankState()
  {
    double actualDistance = getTankDistance(TRIG_PIN_WATER_TANK, ECHO_PIN_WATER_TANK);

    if(maximumDistanceWaterTank == 0)
      return -1;
      
    return 100 - ((actualDistance * 100 ) / maximumDistanceFoodTank);
  }

  boolean WatchMyChicken::calibrateSetMaximumWaterTank()
  {
    maximumDistanceWaterTank = getTankDistance(TRIG_PIN_WATER_TANK, ECHO_PIN_WATER_TANK);
    return true;
  }

  boolean WatchMyChicken::verifyMinimunWater()
  {
    double actualState = getWaterTankState();

    return verifyMinimumTankState(actualState, LED_PIN_LOW_FOOD_AND_WATER);
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

  bool WatchMyChicken::verifyMinimumTankState(double actualState, int ledPinToBlink)
  { 
    if(actualState < CONFIG_MINIMUM_TANK_STATE)
    {
      digitalWrite(ledPinToBlink, HIGH);
      delay(MILLISECONDS_CONFIG_DELAY_LEDS);
      digitalWrite(ledPinToBlink, LOW);
      delay(MILLISECONDS_CONFIG_DELAY_LEDS);
    }
    return true;
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
    int numberOfSecondsFeeding;
    
    numberOfSteps = definedStepsByConfig == 0 ? NUMBER_STEPS_DEFAULT : definedStepsByConfig;
    
    stepperMotorFood.setSpeed(STEPPER_SPEED);
    
    // step 1/100 of a revolution:
    stepperMotorFood.step(STEPPER_STEPS_PER_REV / 100 * numberOfSteps);

    //open
    numberOfSecondsFeeding = feedSecondsConfig == 0 ? SECONDS_FEEDING_CONFIG : feedSecondsConfig;

    numberOfSecondsFeeding = numberOfSecondsFeeding * 1000;

    delay(numberOfSecondsFeeding);

    //close
    stepperMotorFood.step(-(STEPPER_STEPS_PER_REV / 100 * numberOfSteps));
    

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
    if(definedStepsByConfig - STEPPER_CONFIG_INTERVAL < 0)
      return false;
      
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
    if(photocellDefinedDelta - PHOTOCELL_CONFIG_INTERVAL < 0)
      return false;
      
    photocellDefinedDelta = photocellDefinedDelta - PHOTOCELL_CONFIG_INTERVAL; 

    return true;
  }


/*
 * 
 * Open water to the chikens
 * 
 */
  bool WatchMyChicken::openTheWater()
  {
    
    digitalWrite(PIN_WATER_RELAY, HIGH);

    int numberOfseconds =  openedWaterSecondsConfig != 0 ? openedWaterSecondsConfig : OPENED_WATER_SECONDS_CONFIG_DEFAULT;
    
    delay(numberOfseconds);

    digitalWrite(PIN_WATER_RELAY, LOW);
    
    return true;
  }

  int WatchMyChicken::getTheNumberOfSecondsOpenedWater()
  {
    return openedWaterSecondsConfig != 0 ? openedWaterSecondsConfig : OPENED_WATER_SECONDS_CONFIG_DEFAULT;
  }

  bool WatchMyChicken::increaseWaterNumberOfMilliseconds()
  {
    
    openedWaterSecondsConfig = openedWaterSecondsConfig + SECONDS_CONFIG_INTERVAL; 

    return true;
  }

  bool WatchMyChicken::decreaseWaterNumberOfMilliseconds()
  {
    if(openedWaterSecondsConfig - SECONDS_CONFIG_INTERVAL < 0)
      return false;
      
    openedWaterSecondsConfig = openedWaterSecondsConfig - SECONDS_CONFIG_INTERVAL; 

    return true;
  }

  bool WatchMyChicken::openTheGate()
  {

    digitalWrite(PIN_OPEN_GATE_RELAY,HIGH);
  
    digitalWrite(PIN_OPEN_CLOSE_GATE_RELAY,HIGH);
    
    while(!isGateOpened())
    {
      delay(MILLISECONDS_CONFIG_INTERVAL_CLOSE_OPEN_GATE);
    }
  
    digitalWrite(PIN_OPEN_CLOSE_GATE_RELAY,LOW);
    
    digitalWrite(PIN_OPEN_GATE_RELAY, LOW);
  
    return true;
  }
  
  bool WatchMyChicken::closeTheGate()
  {

    delay(1000);

    digitalWrite(PIN_CLOSE_GATE_RELAY,HIGH);

    digitalWrite(PIN_OPEN_CLOSE_GATE_RELAY,HIGH);
    
    while(!isGateClosed())
    {
      delay(MILLISECONDS_CONFIG_INTERVAL_CLOSE_OPEN_GATE);
    }
  
    digitalWrite(PIN_OPEN_CLOSE_GATE_RELAY,LOW);
    
    digitalWrite(PIN_CLOSE_GATE_RELAY, LOW);
  
    return true;
  }

  bool WatchMyChicken::isGateClosed()
  {
    int value=analogRead(CLOSED_GATE_SWITCH_PIN_SENSOR);

    return value < 1000;
  }

  bool WatchMyChicken::isGateOpened()
  {
    int value=analogRead(OPENED_GATE_SWITCH_PIN_SENSOR);
    
    return value < 1000;
  }

  
  
