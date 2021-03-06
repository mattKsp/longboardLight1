/*----------------------------set value----------------------------*/

void setQuickCalibration(uint8_t value)
{
  _doQuickCalibration = value == 0 ? 0 : 1;
  //do not save
  broadcastInt("quickCalibration", _doQuickCalibration);
}

void setFullCalibration(uint8_t value)
{
  _doFullCalibration = value == 0 ? 0 : 1;
  //do not save
  broadcastInt("fullCalibration", _doFullCalibration);
}

/*----------------------------comms - set----------------------------*/
void setSleep(uint8_t value)
{
  mA.sleep = value == 0 ? 0 : 1;
  //do not need to save value
  if (value == 1) { stopComms(); }  //use physical button on board to turn wifi back on again
  broadcastInt("sleep", mA.sleep);
}

void resetDefaults(uint8_t value)
{
  if (value == 1) {
//    clearAllSettings();
    //..don't return the broadcast ???
//    ESP.restart();                          //mabye reset the board aswell ???
  }
}

/*----------------------------set value - safety lights----------------------------*/
void setBreathe(uint8_t value) 
{
  mE.breathe = value == 0 ? 0 : 1;
  EEPROM.write(2, mE.breathe);
  EEPROM.commit();
  broadcastInt("breathe", mE.breathe);
  if (DEBUG) { Serial.println(F("setBreathe(lights)")); }
}

void setHead(uint8_t value) 
{
  mE.head = value == 0 ? 0 : 1;
  EEPROM.write(3, mE.head);
  EEPROM.commit();
  broadcastInt("head", mE.head);
  if (DEBUG) { Serial.println(F("setHead(lights)")); }
}

void setRear(uint8_t value) {
  mE.rear = value == 0 ? 0 : 1;
  EEPROM.write(4, mE.rear);
  EEPROM.commit();
  broadcastInt("rear", mE.rear);
  if (DEBUG) { Serial.println(F("setRear(lights)")); }
}

void setBrake(uint8_t value) {
  mE.brake = value == 0 ? 0 : 1;
  EEPROM.write(5, mE.brake);
  EEPROM.commit();
  broadcastInt("brake", mE.brake);
  if (DEBUG) { Serial.println(F("setBrake(lights)")); }
}

void setIndicate(uint8_t value) {
  mE.indicate = value == 0 ? 0 : 1;
  EEPROM.write(6, mE.indicate);
  EEPROM.commit();
  broadcastInt("indicate", mE.indicate);
  if (DEBUG) { Serial.println(F("setIndicate(lights)")); }
}

/*----------------------------set value - testing----------------------------*/
//turn test modes on/off
void setTestMode(uint8_t value) 
{
  _testMode = value == 0 ? 0 : 1;
  broadcastInt("testMode", _testMode);
}

//set surrent test mode by number
void setCurTestMode(uint8_t value) 
{
  if (value > 11) { value = 11; }
  _curTestMode = value;
  broadcastInt("curTestMode", _curTestMode);
}


//set current test mode by name
void setCurTestModeByName(String name)
{
  for(uint8_t i = 0; i < 1; i++) {
    if(_curTestModesListName[i] == name) {
      setCurTestMode(i);
      break;
    }
  }
}

/*----------------------------set value - led----------------------------*/
void setGlobalBrightness(uint8_t value)
{
  if (value > 255) {
    value = 255;
  } else if (value < 0) {
    value = 0;
  }
  _ledGlobalBrightnessCur = value;
  FastLED.setBrightness(_ledGlobalBrightnessCur);
  EEPROM.write(9, _ledGlobalBrightnessCur);
  EEPROM.commit();
  broadcastInt("globalBrightness", _ledGlobalBrightnessCur);
  if (DEBUG) { Serial.print( F("Global Brightness set to: ") ); Serial.println(_ledGlobalBrightnessCur); }
}

void setHeadBrightness(uint8_t value) {
  //_headLightsBrightness = value;
  _headLightsColHSV.val = value;
  //EEPROM.write(10, _headLightsBrightness);
  EEPROM.write(10, _headLightsColHSV.val);
  EEPROM.commit();
  //broadcastInt("headBrightness", _headLightsBrightness);
  //if (DEBUG) { Serial.print( F("Head Lights Brightness set to: ") ); Serial.println(_headLightsBrightness); }
  broadcastInt("headBrightness", _headLightsColHSV.val);
  if (DEBUG) { Serial.print( F("Head Lights Brightness set to: ") ); Serial.println(_headLightsColHSV.val); }
}

void setRearBrightness(uint8_t value) {
  //_rearLightsBrightness = value;
  _rearLightsColHSV.val = value;
  //EEPROM.write(11, _rearLightsBrightness);
  EEPROM.write(11, _rearLightsColHSV.val);
  EEPROM.commit();
  //broadcastInt("rearBrightness", _rearLightsBrightness);
  //if (DEBUG) { Serial.print( F("Rear Lights Brightness set to: ") ); Serial.println(_rearLightsBrightness); }
  broadcastInt("rearBrightness", _rearLightsColHSV.val);
  if (DEBUG) { Serial.print( F("Rear Lights Brightness set to: ") ); Serial.println(_rearLightsColHSV.val); }
}

void setTrackLightsFadeAmount(uint8_t value) {
  _trackLightsFadeAmount = value;
  EEPROM.write(12, _trackLightsFadeAmount);
  EEPROM.commit();
  broadcastInt("trackLightsFadeAmount", _trackLightsFadeAmount);
  if (DEBUG) { Serial.print( F("Track Lights Fade Amount set to: ") ); Serial.println(_trackLightsFadeAmount); }
}

//void setSolidColor(CRGB color) { setSolidColor(color.r, color.g, color.b); }
//void setSolidColor2(CRGB color2) { setSolidColor2(color2.r, color2.g, color2.b); }

void setSolidColor(uint8_t r, uint8_t g, uint8_t b)
{
  solidColor = CRGB(r, g, b);
  EEPROM.write(13, r);
  EEPROM.write(14, g);
  EEPROM.write(15, b);
  EEPROM.commit();
  broadcastString("color", String(solidColor.r) + "," + String(solidColor.g) + "," + String(solidColor.b));
}

void setSolidColor2(uint8_t r, uint8_t g, uint8_t b)
{
  solidColor2 = CRGB(r, g, b);
  EEPROM.write(16, r);
  EEPROM.write(17, g);
  EEPROM.write(18, b);
  EEPROM.commit();
  broadcastString("color2", String(solidColor2.r) + "," + String(solidColor2.g) + "," + String(solidColor2.b));
}

/*----------------------------set value - main lights sub-mode----------------------------*/
void setMainLightsSubMode(uint8_t value)
{
  if (value >= _mainLightsSubModeTotal) {
    value = _mainLightsSubModeTotal - 1;
  }
  _mainLightsSubMode = value;
  EEPROM.write(8, _mainLightsSubMode);
  EEPROM.commit();
  broadcastInt("subMode", _mainLightsSubMode);
}

void setMainLightsSubModeByName(String name)
{
  for(uint8_t i = 0; i < _mainLightsSubModeTotal; i++) {
    if(patterns[i].name == name) {
      setMainLightsSubMode(i);
      break;
    }
  }
}


//void incrementMainLightsSubMode() {
//  if ( _mainLightsSubMode >= (_mainLightsSubModeTotal - 1) ) {
//    _mainLightsSubMode = 0;    //wrap-around at end back to 0
//  } else {
//    _mainLightsSubMode += 1;   //increase by 1
//  }
//  EEPROM.write(8, _mainLightsSubMode);
//  EEPROM.commit();
//}
//
//void decrementMainLightsSubMode() {
//  if ( _mainLightsSubMode <= 0 ) {
//    _mainLightsSubMode = (byte)(_mainLightsSubModeTotal - 1);    //wrap-around at beginning to the end (1 less than the total)
//  } else {
//    _mainLightsSubMode -= 1;   //decrease by 1
//  }
//  EEPROM.write(8, _mainLightsSubMode);
//  EEPROM.commit();
//}

