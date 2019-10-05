#include "WatchMyChicken.h"

WatchMyChicken watchMyChicken; //the object which control the system

bool isConfigurationMode = true;

void setup() {

  /*
   * Sets the trigPins as an Output
   * Sets the echoPin as an Input
   */
  pinMode(TRIG_PIN_FOOD_TANK, OUTPUT); 
  pinMode(ECHO_PIN_FOOD_TANK, INPUT);
  pinMode(TRIG_PIN_WATER_TANK, OUTPUT); 
  pinMode(ECHO_PIN_WATER_TANK, INPUT);

  pinMode(TEMPERATURE_PIN_SENSOR, INPUT);

  pinMode(PIN_WATER_RELAY, OUTPUT);



  pinMode(8, OUTPUT); 
  
  
  Serial.begin(9600); // Starts the serial communication
  Serial.println("Arduino ready to read commands.");
  printConfigCommands();
}

void loop() {

/*
  
  
  
  double actualTemperature = watchMyChicken.getActualTemperature();
  Serial.print("Actual Temperature: ");
  Serial.println(actualTemperature);

  watchMyChicken.feedsTheChickens();
  Serial.println("Was feeded the chickens");
  */

  if (Serial.available() > 0) {

    if(isConfigurationMode)
    {
      
      // read the incoming byte:
      String command = Serial.readString();

      //Serial.println("Command printed: " + command);

      boolean result = processCommand(command);

      if(result == false)
        Serial.println("\nError processing the command.");

      if(isConfigurationMode)
          printConfigCommands();
    }
  }

  if(!isConfigurationMode)
  {
    bool isNight = watchMyChicken.isNight();
      Serial.print("isNight: ");
      Serial.println(isNight);

      double foodTankState = watchMyChicken.getFoodTankState();
      Serial.print("Food Tank State: ");
      Serial.println(foodTankState);

      double waterTankState = watchMyChicken.getWaterTankState();
      Serial.print("Water Tank State: ");
      Serial.println(waterTankState);

      
      digitalWrite(8, HIGH);
      delay(2000);
      digitalWrite(8, LOW);
      delay(2000);
  }
  
}

void printConfigCommands()
{
  Serial.println("Watch My Chikens Config:");
  Serial.println("1- Config: Increase photocell delta");
  Serial.println("2- Config: Decrease photocell delta");
  
  Serial.println("3- Config: Increase number of steps of step motor");
  Serial.println("4- Config: Decrease number of steps of step motor");
  Serial.println("5- TEST: feed the chickens");
  
  Serial.println("6- Config: Increase number of seconds as open");
  Serial.println("7- Config: Decrease number of seconds as open");
  Serial.println("8- TEST: open the water");
  
  
  Serial.println("4- Calibration: Set as maximum water");
  Serial.println("5- Calibration: Set as minimum water");
  Serial.println("6- Calibration: Set as maximum feed");
  Serial.println("7- Calibration: Set as minimum feed");

  
  Serial.println("99- Get all configs");
  Serial.println("100- Exit from configurantion mode");
  Serial.println("Command:");
}

boolean processCommand(String commandTmp)
{
  int command, value;
  
  //validations...
  if (commandTmp == NULL || commandTmp.length() == 0)
    return false;

  command = commandTmp.toInt();

  Serial.print("Command readed (INT): ");
  Serial.println(command);
      
  switch(command)
  {
    case 1:
      return watchMyChicken.increasePhotocellDelta();
    break;
    
    case 2:
      return watchMyChicken.decreasePhotocellDelta();
    break;
    
    case 3:
      return watchMyChicken.increaseNumberOfSteps();
    break;
    
    case 4:
      return watchMyChicken.decreaseNumberOfSteps();
    break;
    
    case 5:
      return watchMyChicken.feedsTheChickens();
    break;

    case 6:
      return watchMyChicken.increaseNumberOfMilliseconds();
    break;
    
    case 7:
      return watchMyChicken.decreaseNumberOfMilliseconds();
    break;
    case 8:
      return watchMyChicken.openTheWater();
    break;

    
    
    case 99:
      Serial.println("------------------------------------");
      Serial.print("Actual defined delta of photocell: ");
      Serial.println(watchMyChicken.getPhotocellDelta());
      
      Serial.print("Is night: ");
      Serial.println(watchMyChicken.isNight());
      
      Serial.print("Actual defined Steps:");
      Serial.println(watchMyChicken.getActualConfigNumberOfStepsMotor());

      Serial.print("Number of milliseconds as open water:");
      Serial.println(watchMyChicken.getTheNumberOfSecondsOpenedWater());
      
      Serial.println("------------------------------------");
      return true;  
    break;
  }

  return false;
}
