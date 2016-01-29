/*
 13 light/solenoid pairs
 5 "routines"
 
 Light and solenoid pairs should be triggered at the same time,
 but the duration of the light needs to be adjustable
 */

// set the number of light/solenoid pairs
const int PAIRS = 13;

// define AC pins (22-34) for lights
const int LIGHTS[] = {
  22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34
};

// define DC pins (38-50) for solenoids
const int SOLENOIDS[] = {
  38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50
};

// sets how long should the solenoid be on (in millis)
const double solenoidOnDuration = 5;

// array to store each light-on delay in millis()
double lightOnDelay[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// array to store each light-on duration in millis()
double lightOnDuration[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// array to store each light-on state | 0 = off, 1 = on
int lightOnState[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

int lightsCurrentlyOn[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// "running" flag
boolean IS_RUNNING;

// holds the routine number we are currently running
long current_routine;

// holds the start time (in millis) of our timer
double startTime;

// tells us how many lights are currently still on
int lightsOn;

// sets the duration of the gap between routines
double routineGap;

boolean INIT;


int delayVal;
int onVal;

void setup()
{
  // INITIALIZE PINS
  for(int i=0; i< PAIRS; i++){

    // AC pins
    pinMode(LIGHTS[i], OUTPUT);
    digitalWrite(LIGHTS[i], LOW);

    // DC pins
    pinMode(SOLENOIDS[i], OUTPUT);
    digitalWrite(SOLENOIDS[i], LOW);
  }   

  // INITIALIZE STATES
  IS_RUNNING = false;
  INIT = true;
  current_routine = 0;
  startTime = 0;
  lightsOn = 0;
  routineGap = 0;
}

void loop()
{
  render();
}
