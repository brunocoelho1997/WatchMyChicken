#include "WatchMyChicken.h"
#include "Utils.h"


WatchMyChicken watchMyChicken; //the object which control the system

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
  
  
  Serial.begin(9600); // Starts the serial communication
}

void loop() {

  double foodTankState = watchMyChicken.getFoodTankState();
  Serial.print("Food Tank State: ");
  Serial.println(foodTankState);

  double waterTankState = watchMyChicken.getWaterTankState();
  Serial.print("Water Tank State: ");
  Serial.println(waterTankState);
  
  double actualTemperature = watchMyChicken.getActualTemperature();
  Serial.print("Actual Temperature: ");
  Serial.println(actualTemperature);
  
  delay(1000);
}
