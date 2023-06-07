#include <Arduino.h>
#include "GPS.h"

SensorGPS::SensorGPS():gps(),fix(){}

void SensorGPS::Calibrate() 
{
    while(gps.available(Serial3) > 0)
    {
        fix = gps.read();
    }
}

byte SensorGPS::getDate() 
{
    if(fix.valid.date) 
    {
        return fix.dateTime.date;
    }
    else
    {
        return 254;
    }
}
