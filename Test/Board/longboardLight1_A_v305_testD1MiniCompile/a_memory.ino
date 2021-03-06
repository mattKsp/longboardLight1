/*----------------------------memory load/save---------------------*/

/*
 * NOTE - all eeprom saves will be wiped when a new sketch is uploaded, but will persist thru normal use.
 * 
 * Settings to save (512 total)
 * 
 * 0=   BLANK
 * 1=  _breathingEnabled          - boolean
 * 2=  _headLightsEnabled         - boolean
 * 3=  _rearLightsEnabled         - boolean
 * 4=  _indicatorsEnabled         - boolean
 * 5=   BLANK
 * 6=   BLANK
 * 7=   system save indicator     = 0/1
 * 8=  _mainLightsSubMode         - 0-255
 * 9=  _ledGlobalBrightnessCur    - 0-255
 * 10= _headLightsBrightness      - 0-255
 * 11= _rearLightsBrightness      - 0-255
 * 12= _trackLightsFadeAmount ??? - 0-255
 * 
 * 
 */
void setDefaultSettings() {
  #ifdef DEBUG
    Serial.print(F("Setting default settings"));
    Serial.println();
  #endif
  
  mE = { true, true, true, true, true, false };       // Enabled 
  mA = { false, false, true, true, false, false };    // Active

  _mainLightsSubMode = 2;  //3
  _ledGlobalBrightnessCur = 255;
  setHeadLightsBrightness(200);
  setRearLightsBrightness(200);
  _trackLightsFadeAmount = 16;

  //offsets not done yet, requires splitting numbers, or just wait till get replacement board with WIFI/Bluetooth and more memory
  //_mpu6050AccelOffset[3] = {436, 1956, 1318};       //XYZ accel offsets to write to the MPU6050 - get from full calibration and save to memory
  //_mpu6050GyroOffset[3] = {9, -32, 69};             //XYZ gyro offsets to write to the MPU6050 - get from full calibration and save to memory
}

void loadAllSettings() {
  //this gets called at the beginning of setup.
  EEPROM.begin(512);
  
  //if system settings saved flag set at pos 7 is '1', then we have system data to be read from memory.. failsafe
  if (EEPROM.read(7) == 1) {
    #ifdef DEBUG
      Serial.print(F("Loading settings"));
      Serial.println();
    #endif
    //redo these later into 1 bit mask
    if (EEPROM.read(1) == 255) { mE.breathe = true; }  //modes[1].breathe = true;
    else { mE.breathe = false; }
    if (EEPROM.read(2) == 255) { mE.head = true; }
    else { mE.head = false; }
    if (EEPROM.read(3) == 255) { mE.rear = true; }
    else { mE.rear = false; }
    if (EEPROM.read(4) == 255) { mE.indicate = true; }
    else { mE.indicate = false; }
    
    _mainLightsSubMode = EEPROM.read(8);  
    _ledGlobalBrightnessCur = EEPROM.read(9);
    setHeadLightsBrightness( EEPROM.read(10) );
    setRearLightsBrightness( EEPROM.read(11) );
    _trackLightsFadeAmount = EEPROM.read(12);
  } else {
    //set defaults then saveSettings
    setDefaultSettings();
    saveAllSettings();
  }
}

void saveAllSettings() {
  #ifdef DEBUG
    Serial.print(F("Saving settings"));
    Serial.println();
  #endif
    
  //redo these later into 1 bit mask
  if (mE.breathe == true) { EEPROM.write(1, 255); }
  else { EEPROM.write(1, 0); }
  if (mE.head == true) { EEPROM.write(2, 255); }
  else { EEPROM.write(2, 0); }
  if (mE.rear == true) { EEPROM.write(3, 255); }
  else { EEPROM.write(3, 0); }
  if (mE.indicate == true) { EEPROM.write(4, 255); }
  else { EEPROM.write(4, 0); }
    
  EEPROM.write(7, 1); //write a 1 to pos 7 to indicate that system data has been saved and is available for use.

  EEPROM.write(8, _mainLightsSubMode);
  EEPROM.write(9, _ledGlobalBrightnessCur);
  EEPROM.write(10, _headLightsBrightness);
  EEPROM.write(11, _rearLightsBrightness);
  EEPROM.write(12, _trackLightsFadeAmount);

  EEPROM.commit();
}

void clearAllSettings() {
  #ifdef DEBUG
    Serial.print(F("Clearing settings"));
    Serial.println();
  #endif
  for (int i = 0 ; i < 512; i++) {
    EEPROM.write(i, 0);
  } // TEMP
  
  EEPROM.commit();
  
  setDefaultSettings();
  saveAllSettings();
}


