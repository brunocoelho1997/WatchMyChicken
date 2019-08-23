#include "WatchMyChicken.h"
#include "Utils.h"


WatchMyChicken watchMyChicken; //the object which control the system

void setup() {

  /*
   * Sets the trigPins as an Output
   * Sets the echoPin as an Input
   */
  pinMode(trigPinFoodTank, OUTPUT); 
  pinMode(echoPinFoodTank, INPUT);
  pinMode(trigPinWaterTank, OUTPUT); 
  pinMode(echoPinWaterTank, INPUT);
  
  Serial.begin(9600); // Starts the serial communication
}

void loop() {

  double foodTankState = watchMyChicken.getFoodTankState();
  Serial.print("Food Tank State: ");
  Serial.println(foodTankState);
  
  delay(1000);
}
