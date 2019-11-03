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
  pinMode(LED_PIN_LOW_FOOD_AND_WATER, OUTPUT);
  
  pinMode(TRIG_PIN_WATER_TANK, OUTPUT); 
  pinMode(ECHO_PIN_WATER_TANK, INPUT);
  
  pinMode(TEMPERATURE_PIN_SENSOR, INPUT);

  pinMode(PIN_WATER_RELAY, OUTPUT);

  pinMode(PIN_OPEN_CLOSE_GATE_RELAY, OUTPUT); 
  pinMode(PIN_OPEN_GATE_RELAY, OUTPUT); 
  pinMode(PIN_CLOSE_GATE_RELAY, OUTPUT); 
  
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

    Serial.print("Is gate opened:");
    Serial.println(watchMyChicken.isGateOpened());

    Serial.print("Is gate closed:");
    Serial.println(watchMyChicken.isGateClosed());

    watchMyChicken.verifyMinimunFood();

    watchMyChicken.verifyMinimunWater();

    //if is night and the gate is open...
    if(watchMyChicken.isNight() && watchMyChicken.isGateOpened())
    {  
        //watchMyChicken.feedsTheChickens();
        //watchMyChicken.openTheWater();

        //delay(5000); //5 seconds waiting to all chickens go inside the "house" and close the gate

        Serial.print("vai fechar portao");
   
        watchMyChicken.closeTheGate();

        delay(2000);
    }
    //if is day and the gate is closed...
    else if(!watchMyChicken.isNight() && watchMyChicken.isGateClosed())
    {
        //watchMyChicken.feedsTheChickens();
        //watchMyChicken.openTheWater();

                
        Serial.print("vai abrir portao");
        
        watchMyChicken.openTheGate();

        delay(2000);
    }
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

  Serial.println("9- Calibration: Set as maximum food");
  Serial.println("10- Calibration: Set as maximum water");

  Serial.println("13- TEST: Open the gate");
  Serial.println("14- TEST: Close the gate");
  
  
  
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
      Serial.println("Was feeded the chickens");
    break;

    case 6:
      return watchMyChicken.increaseWaterNumberOfMilliseconds();
    break;
    
    case 7:
      return watchMyChicken.decreaseWaterNumberOfMilliseconds();
    break;
    case 8:
      return watchMyChicken.openTheWater();
    break;

    case 9:
      return watchMyChicken.calibrateSetMaximumFoodTank();
    break;
    
    case 10:
      return watchMyChicken.calibrateSetMaximumWaterTank();
    break;
    
    case 13:
      return watchMyChicken.openTheGate();
    break;

    case 14:
      return watchMyChicken.closeTheGate();
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

      Serial.print("Is gate opened:");
      Serial.println(watchMyChicken.isGateOpened());

      Serial.print("Is gate closed:");
      Serial.println(watchMyChicken.isGateClosed());

      Serial.println("------------------------------------");
      return true;  
    break;

    case 100:
      isConfigurationMode = false;
      //Serial.end(); // finish the serial communication. Temporary line of code - since we are using arduino UNO and all I/O are used we need to use the pin 1
    break;
  }

  return false;
}
