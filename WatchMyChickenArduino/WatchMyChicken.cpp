#include "WatchMyChicken.h"

  // Connected to L298N Motor Driver In1, In2, In3, In4 
  // Pins entered in sequence 1-2-3-4 for proper step sequencing
  Stepper stepperMotorFood(STEPPER_STEPS_PER_REV, STEPPER_MOTOR_IN1, STEPPER_MOTOR_IN2, STEPPER_MOTOR_IN3, STEPPER_MOTOR_IN4);
    
  WatchMyChicken::WatchMyChicken(){    
    isGateClosed = true;
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
    if(actualState < MILLISECONDS_CONFIG_MINIMUM_TANK_STATE)
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
    numberOfSecondsFeeding = feedMilliSecondsConfig == 0 ? MILLISECONDS_FEEDING_CONFIG : feedMilliSecondsConfig;
    
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

    //Serial.print("Analog reading PHOTOCELL_PIN_SENSOR = ");
    //Serial.println(photocellReading);

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

    int numberOfMiliseconds =  openedWaterMilliSecondsConfig != 0 ? openedWaterMilliSecondsConfig : OPENED_WATER_MILLISECONDS_CONFIG_DEFAULT;
    
    delay(numberOfMiliseconds);

    digitalWrite(PIN_WATER_RELAY, LOW);
    
    return true;
  }

  int WatchMyChicken::getTheNumberOfSecondsOpenedWater()
  {
    return openedWaterMilliSecondsConfig != 0 ? openedWaterMilliSecondsConfig : OPENED_WATER_MILLISECONDS_CONFIG_DEFAULT;
  }

  bool WatchMyChicken::increaseWaterNumberOfMilliseconds()
  {
    
    openedWaterMilliSecondsConfig = openedWaterMilliSecondsConfig + MILLISECONDS_CONFIG_INTERVAL; 

    return true;
  }

  bool WatchMyChicken::decreaseWaterNumberOfMilliseconds()
  {
    if(openedWaterMilliSecondsConfig - MILLISECONDS_CONFIG_INTERVAL < 0)
      return false;
      
    openedWaterMilliSecondsConfig = openedWaterMilliSecondsConfig - MILLISECONDS_CONFIG_INTERVAL; 

    return true;
  }

  bool WatchMyChicken::openTheGate()
  {

    int numberOfSecondsGate;

    if(!isGateClosed)
      return false;
      
    numberOfSecondsGate = gateMilliSecondsConfig == 0 ? MILLISECONDS_CONFIG_INTERVAL_CLOSE_OPEN_GATE : gateMilliSecondsConfig;
    
    digitalWrite(PIN_OPEN_GATE_RELAY,HIGH);
  
    digitalWrite(PIN_OPEN_CLOSE_GATE_RELAY,HIGH);
    
    delay(numberOfSecondsGate);
  
    digitalWrite(PIN_OPEN_CLOSE_GATE_RELAY,LOW);
    
    digitalWrite(PIN_OPEN_GATE_RELAY, LOW);
  
    isGateClosed = false;
      
    return true;
  }
  
  bool WatchMyChicken::closeTheGate()
  {
    int numberOfSecondsGate;

    if(isGateClosed)
      return false;
    
    numberOfSecondsGate = gateMilliSecondsConfig == 0 ? MILLISECONDS_CONFIG_INTERVAL_CLOSE_OPEN_GATE : gateMilliSecondsConfig;
    
    digitalWrite(PIN_CLOSE_GATE_RELAY,HIGH);
  
    digitalWrite(PIN_OPEN_CLOSE_GATE_RELAY,HIGH);
    
    delay(numberOfSecondsGate);
  
    digitalWrite(PIN_OPEN_CLOSE_GATE_RELAY,LOW);
    
    digitalWrite(PIN_CLOSE_GATE_RELAY, LOW);

    isGateClosed = true;
      
    return true;
  }

  bool WatchMyChicken::increaseGateNumberOfMilliseconds()
  {

    Serial.print("isGateClosed: ");
      Serial.println(isGateClosed);
      
    if(!isGateClosed)
      return false;
    
    gateMilliSecondsConfig = gateMilliSecondsConfig + MILLISECONDS_CONFIG_INTERVAL_CLOSE_OPEN_GATE; 

    return true;
  }

  bool WatchMyChicken::decreaseGateNumberOfMilliseconds()
  {

Serial.print("isGateClosed: ");
      Serial.println(isGateClosed);
      
    if(!isGateClosed)
      return false;
    
    if(gateMilliSecondsConfig - MILLISECONDS_CONFIG_INTERVAL_CLOSE_OPEN_GATE < 0)
      return false;
      
    gateMilliSecondsConfig = gateMilliSecondsConfig - MILLISECONDS_CONFIG_INTERVAL_CLOSE_OPEN_GATE; 

    return true;
  }

  int WatchMyChicken::getTheNumberOfSecondsOpenCloseGate()
  {
    return gateMilliSecondsConfig != 0 ? gateMilliSecondsConfig : MILLISECONDS_CONFIG_INTERVAL_CLOSE_OPEN_GATE;
  }

  
  
