/* ===================================================================== 
 SET UP OUR ROUTINES
 */
void setRoutine()
{
  // choose a routine at random (1, [number of routines] + 1)
//  current_routine = round( random(1, 4) );
  current_routine++;
  if(current_routine > 5) current_routine = 1;

  // set up the routine
  switch(current_routine){

  default:
    break;

  case 1:  // center then outer

    // Turn On Delay in MILLIS
    
    // CENTER
    lightOnDelay[0] = 0;
    
    // INNER
    lightOnDelay[1] = 2500;
    lightOnDelay[2] = 2500;
    lightOnDelay[3] = 2500;
    lightOnDelay[4] = 2500;
    lightOnDelay[5] = 2500;
    lightOnDelay[6] = 2500;
    
    // Turn On Duration in MILLIS
    lightOnDuration[0] = 5000;
    lightOnDuration[1] = 5000;
    lightOnDuration[2] = 5000;
    lightOnDuration[3] = 5000;
    lightOnDuration[4] = 5000;
    lightOnDuration[5] = 5000;
    lightOnDuration[6] = 5000;

    // no you touch this loop!
    for(int i=0; i < PAIRS; i++){
      lightOnDuration[i] += lightOnDelay[i];
    }

    break;


  case 2: // all at once

    // Turn On Delay in MILLIS
    
    // CENTER
    lightOnDelay[0] = 0;
    
    // INNER
    lightOnDelay[1] = 0;
    lightOnDelay[2] = 0;
    lightOnDelay[3] = 0;
    lightOnDelay[4] = 0;
    lightOnDelay[5] = 0;
    lightOnDelay[6] = 0;
    
    // On Duration in MILLIS
    
    //CENTER
    lightOnDuration[0] = 5000;
    
    //INNER
    lightOnDuration[1] = 5000;
    lightOnDuration[2] = 5000;
    lightOnDuration[3] = 5000;
    lightOnDuration[4] = 5000;
    lightOnDuration[5] = 5000;
    lightOnDuration[6] = 5000;

    // no you touch this loop!
    for(int i=0; i < PAIRS; i++){
      lightOnDuration[i] += lightOnDelay[i];
    }
    break;

  case 3: // chase

    // Turn On Delay in MILLIS
    
    for(int i=0; i < PAIRS; i++){
      lightOnDelay[i] = i*1000;
      lightOnDuration[i] = 1000;
    }

    // no you touch this loop!
    for(int i=0; i < PAIRS; i++){
      lightOnDuration[i] += lightOnDelay[i];
    }
    break;

  case 4: 

    // CENTER
    lightOnDelay[0] = 2500;
    
    // INNER
    lightOnDelay[1] = 0;
    lightOnDelay[2] = 0;
    lightOnDelay[3] = 0;
    lightOnDelay[4] = 0;
    lightOnDelay[5] = 0;
    lightOnDelay[6] = 0;
    
    // On Duration in MILLIS
    
    //CENTER
    lightOnDuration[0] = 6000;
    
    //INNER
    lightOnDuration[1] = 6000;
    lightOnDuration[2] = 6000;
    lightOnDuration[3] = 6000;
    lightOnDuration[4] = 6000;
    lightOnDuration[5] = 6000;
    lightOnDuration[6] = 6000;

    break;

  case 5: 

    lightOnDelay[0] = 0;
    lightOnDuration[0] = random(2000, 5000);
    
    for(int i=1; i < 7; i++){
    
      // sets random light-on delay times in millis
      delayVal = random(5000);
      lightOnDelay[i] = delayVal;
      
//      onVal = lightOnDelay[i] + 2500;
      onVal = lightOnDelay[i] + (5000 - lightOnDelay[i]);
      // sets random light-on duration times in millis
      lightOnDuration[i] = onVal;
    }
    break;

  case 6: // PRECISION EXAMPLE

    lightOnDelay[0] = 0;
    lightOnDuration[0] = random(5000, 7000);
       
    // sets random light-on delay times in millis
    delayVal = random(7000);
    lightOnDelay[1] = delayVal;
    lightOnDelay[11] = delayVal;
    
    onVal = random(5000, 7000) + lightOnDelay[1];
    lightOnDuration[1] = onVal;

    delayVal = random(7000);
    lightOnDelay[2] = delayVal;
    
    onVal = random(5000, 7000) + lightOnDelay[2];
    lightOnDuration[2] = onVal;

    delayVal = random(7000);
    lightOnDelay[3] = delayVal;
    
    onVal = random(5000, 7000) + lightOnDelay[3];
    lightOnDuration[3] = onVal;

    delayVal = random(7000);
    lightOnDelay[4] = delayVal;
    
    onVal = random(5000, 7000) + lightOnDelay[4];
    lightOnDuration[4] = onVal;
    
    delayVal = random(7000);
    lightOnDelay[5] = delayVal;
    
    onVal = random(5000, 7000) + lightOnDelay[5];
    lightOnDuration[5] = onVal;
    
    delayVal = random(7000);
    lightOnDelay[6] = delayVal;
    
    onVal = random(5000, 7000) + lightOnDelay[6];
    lightOnDuration[6] = onVal;
    
    break;

  }

  // set our initial read time
  startTime = millis();

  // let the controller know that we are running
  IS_RUNNING = true;

  // set all our lightsOn
  lightsOn = PAIRS;

  // set a random 'pause' time after the routine (in millis)
//  routineGap = random(1000, 10000);


}


/* ===================================================================== 
 MAIN CONTROLLER - no you touch 
 */
void render()
{

  IS_RUNNING = checkRunning();

  // do stuff if we are running
  if(IS_RUNNING || INIT)
  {
    INIT = false;

    // loop through our pairs
    for(int i=0; i < PAIRS; i++)
    {

      /* --------------------------------------------------------------
       LIGHT STATES */

      // if the light-on delay has been exceeded AND the light state is OFF, set the light state to ON
      if( millis() - startTime >= lightOnDelay[i] && millis() - startTime < lightOnDuration[i] && lightOnState[i] == 0 )
      {
        lightOnState[i] = 1;   // update the state array
        lightOn(i);            // turn the light ON
        solenoidOn(i);         // turn the solenoid ON

      }

      // if the light-on duration AND the light state is ON, set the light state to OFF
      if( millis() - startTime >= lightOnDuration[i] && lightOnState[i] == 1 )
      {
        lightOnState[i] = 0;  // update the state array
//        lightOff(i);          // turn the light OFF
        lightsOn--;          // update our lightsOn count 
      } 

      /* --------------------------------------------------------------
       SOLENOID STATES */

      // check if the solenoid should be turned off
      solenoidOff(i);  
    }



  } 

  if (!IS_RUNNING)
  {

    // pause after routine
    delay(routineGap);

    // set up the next routine
    setRoutine();
  }

}

/* ===================================================================== 
 LIGHT CONTROLS - no you touch
 */
void lightOn(int i)
{
  digitalWrite(LIGHTS[i], HIGH);
}

void lightOff(int i)
{
  digitalWrite(LIGHTS[i], LOW);
  return;
}

/* =====================================================================
 SOLENOID CONTROLS - no you touch
 */

void solenoidOn(int i)
{
  digitalWrite(SOLENOIDS[i], HIGH);
}

void solenoidOff(int i)
{
  if( millis() - startTime >= lightOnDelay[i] + solenoidOnDuration )
  {
    digitalWrite(SOLENOIDS[i], LOW);
  } 

}

/* ===================================================================== 
 RUNNING CHECK - no you touch
 */
boolean checkRunning()
{
  if(lightsOn == 0)
  {
    return false;
  } 
  else 
  {
    return true;
  }  
}

