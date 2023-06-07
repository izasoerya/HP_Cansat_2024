#ifndef GPS_H
#define GPS_H

#include <NMEAGPS.h>

class SensorGPS 
{
private:
    NMEAGPS gps;
    gps_fix fix;
public:
    SensorGPS();
    void Calibrate();
    byte getSecond();
    byte getMinute();
    byte getHour();
    byte getDate();
    byte getMonth();
    byte getYear();
};

#endif