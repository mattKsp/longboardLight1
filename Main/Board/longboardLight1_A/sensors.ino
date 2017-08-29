/*----------------------------sensors----------------------------*/

void setupSensors() {
  //setting up wheel pin using '_wheelSensorPin' because hard to handle interrupts from inside a library.
  
  w.Init(0, _wheelSensorPin[0], 0.0345, 8); //currently only using 1 sensor/wheel. 
  //w.SetupWheel(1, _wheelSensorPin[1], 0.0345, 8);  
  
  o.Init(); //need to pass values if any available from memory
  //o.InitWithVars(a[3], b[3]);
}

/* Sensor input loop (called from Main loop) */
void loopSensors() {
  loopOrientation();
  loopWheel();
}

/*----------------------------MPU6050 sensor----------------------------*/
void loopOrientation() {
  EVERY_N_MILLISECONDS(_mpu6050ReadInterval) { o.ReadFiltered(); }
  if (o.GetOrientation() == 0 &&_mainLightsSubMode == 3) { o.ReadDirection(); }
  EVERY_N_MILLISECONDS(_orientationInterval) { o.ReadOrientation(); }
}

/*----------------------------wheel sensors----------------------------*/
/* Wheel tracking */
void loopWheel() {
  #ifdef DATA_LOGGING 
    EVERY_N_MILLISECONDS(1000) {                     //FastLED based non-blocking delay to update/display the sequence.
      detachInterrupt(0);     //..no interrupts whilst we process !!!
      w.DoUpdate(o.GetDirection()); // !!! need to swap '_directionCur' for a direct line to the mpu6050 library var !!!
      attachInterrupt(digitalPinToInterrupt(_wheelSensorPin[0]), wheelInterrupt0, CHANGE);  //re-attach the interrupt !!!
    } //END timed-loop
  #endif  //END if DATA_LOGGING
} //END loopWheel

