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

//photocell sensor constants
const int PHOTOCELL_PIN_SENSOR = A1;
const int DEFAULT_PHOTOCELL_DELTA = 600;
const int PHOTOCELL_CONFIG_INTERVAL = 100;

//stepper motor pins
const int STEPPER_MOTOR_IN1 = 2;
const int STEPPER_MOTOR_IN2 = 3;
const int STEPPER_MOTOR_IN3 = 4;
const int STEPPER_MOTOR_IN4 = 5;

// Stepper Motor - Number of steps per output rotation
const int STEPPER_STEPS_PER_REV = 200;
const int STEPPER_SPEED = 40;
const int NUMBER_STEPS_DEFAULT = 70;
const int STEPPER_CONFIG_INTERVAL = 25;


//constants of relay (when open the water to the chickens)
const int PIN_WATER_RELAY = 6;
const int OPENED_WATER_MILLISECONDS_CONFIG_DEFAULT = 5000;
const int MILLISECONDS_CONFIG_INTERVAL = 1000;
