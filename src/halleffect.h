#ifndef HALLEFFECT_H
#define HALLEFFECT_H
#include "Arduino.h"

class HALLEFFECT
{
private:
    int _pin;
    int _rpm;
    volatile int _revs = 0;
public:
    void sensor_begin(int pin);
    void sensor_update();
    unsigned long getRpm();
    unsigned int getRevs();
    void resetRevs();
    void sensorPurse();
};

#endif