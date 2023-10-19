#include "halleffect.h"

int _object = 0;
unsigned long current_millis;
int state = 1;
int lastState = 1;

volatile int count, countold;
void rpm()
{
    _object++;
    count++;
}
void HALLEFFECT::sensor_begin(int pin)
{
    this->_pin = pin;
    attachInterrupt(digitalPinToInterrupt(_pin), rpm, FALLING);
    pinMode(_pin, INPUT);
}
void HALLEFFECT::sensor_update()
{
    if(millis() - current_millis > 1000)
    {
        _rpm = _object * 60;
        _object = 0;
        current_millis = millis();
    }

    // state = digitalRead(_pin);
    // if(lastState && !state)
    // {
    //   lastState = state;
    // } else if(!lastState && state)
    // {
    //   _revs++;
    //   lastState = 1;
    // }
    if(_revs != count)
    {
      Serial.println(count);
      _revs = count;
    }
}
void HALLEFFECT::sensorPurse()
{
  count = _revs;
}
void HALLEFFECT::resetRevs()
{
  _revs = 0;
  count =0;
}
unsigned int HALLEFFECT::getRevs()
{
  return _revs;
}
unsigned long HALLEFFECT::getRpm()
{
    return _rpm;
}