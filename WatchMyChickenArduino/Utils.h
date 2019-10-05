//Pins 

//food level sensor pins
const int TRIG_PIN_FOOD_TANK = 10;
const int ECHO_PIN_FOOD_TANK = 11;

//water level sensor pins
const int TRIG_PIN_WATER_TANK = 12;
const int ECHO_PIN_WATER_TANK = 13;

//used by water and food level sensor calculus
const double SOUND_AIR_SPEED = 0.034;

//temperature sensor pin
const int TEMPERATURE_PIN_SENSOR = A0;

//stepper motor pins
const int STEPPER_MOTOR_IN1 = 2;
const int STEPPER_MOTOR_IN2 = 3;
const int STEPPER_MOTOR_IN3 = 4;
const int STEPPER_MOTOR_IN4 = 5;

// Stepper Motor - Number of steps per output rotation
const int STEPPER_STEPS_PER_REV = 200;
const int STEPPER_SPEED = 40;
const int NUMBER_STEPS_DEFAULT = 70;