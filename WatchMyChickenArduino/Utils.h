//Pins 

const int SECONDS_WAITING_CONFIG_MODE = 30; //can't set a higher value than 30000

const int DELAY_SECONDS_CONFIGURATION_MODE = 1;

const int DELAY_SECONDS_NOT_CONFIGURATION_MODE = 30;

//food level sensor pins
const int TRIG_PIN_FOOD_TANK = 10;
const int ECHO_PIN_FOOD_TANK = 11;

const int LED_PIN_LOW_FOOD_AND_WATER = 1;

const int LED_PIN_PING = 0;


//water level sensor pins
const int TRIG_PIN_WATER_TANK = 12;
const int ECHO_PIN_WATER_TANK = 13;

const int MILLISECONDS_CONFIG_DELAY_LEDS = 2000;

//if the percentage of the tank is lower tha  20 the arduino active a led
const int CONFIG_MINIMUM_TANK_STATE = 20;

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
const int STEPPER_SPEED = 100;
const int NUMBER_STEPS_DEFAULT = 10;
const int STEPPER_CONFIG_INTERVAL = 1;
const int MILLISECONDS_FEEDING_CONFIG = 5000;

//constants of relay (when open the water to the chickens)
const int PIN_WATER_RELAY = 6;
const int OPENED_WATER_MILLISECONDS_CONFIG_DEFAULT = 5000;
const int MILLISECONDS_CONFIG_INTERVAL = 1000;

//
const int PIN_OPEN_CLOSE_GATE_RELAY = 7; //if this PIN are setted as low the gate will not open neither close
const int PIN_OPEN_GATE_RELAY = 8;
const int PIN_CLOSE_GATE_RELAY = 9;
const int MILLISECONDS_CONFIG_INTERVAL_CLOSE_OPEN_GATE = 50;
//gate sensors pins
const int OPENED_GATE_SWITCH_PIN_SENSOR = A2;
const int CLOSED_GATE_SWITCH_PIN_SENSOR = A3;
