
byte _tinyGDataPin = 14;//connected to spindle direction (Sdir)
byte _tinyGClockPin = 7;//connected to spindle on (Spin)

boolean _clockState = false;
boolean _lastClockState = false;
boolean _debouncedClockState = false;
byte _maxDebounceTime = 5;
byte _clockDebounceCounter = _maxDebounceTime;

byte _messageSize = 3;

byte _dataPosition = 0;
byte _tinyGMessage = 0;

long _messageStartTime = 0;


void initTinyGComm()
{
  pinMode(_tinyGDataPin, INPUT);
  pinMode(_tinyGClockPin, INPUT);
}

void checkTinyG()
{
  _clockState = digitalRead(_tinyGClockPin);
  if (_checkClockDebounce())  _readTinyGMessage();
  _lastClockState = _clockState;
}

boolean _checkClockDebounce(){
  if ((_clockState != _lastClockState) && (_clockState != _debouncedClockState)){
    if (_clockState) {
      _debouncedClockState = true;
      return true;
    } else {
      _clockDebounceCounter = _maxDebounceTime;
    }
  } else if ((_clockState == _lastClockState) && (_clockState != _debouncedClockState)){
    if (_clockDebounceCounter > 0 && --_clockDebounceCounter == 0) {
      _debouncedClockState = _clockState;
      if (_debouncedClockState) return true;
    }
  }
  return false;
}

void _readTinyGMessage() {
   if (_dataPosition==0){
        _messageStartTime=millis();
        _tinyGMessage = 0;
   } else if(millis() - _messageStartTime > 500){
//     Serial.print("clear");
     _messageStartTime = millis();
     _dataPosition = 0;
     _tinyGMessage = 0;
   }
   _tinyGMessage += (digitalRead(_tinyGDataPin) << (_messageSize - 1 - _dataPosition));
   _dataPosition++;
   if (_dataPosition >= _messageSize){
     byte output = _tinyGMessage;
     _dataPosition = 0; 
     _tinyGMessage = 0;
     Serial.println(output, BIN);
     handleTinyGMessage(output);
   }
}
  
