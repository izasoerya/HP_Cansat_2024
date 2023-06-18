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
    float getLatitude();
    float getLongitude();
    float getAltitudeGPS();
    byte getSatCount();
    void getCurrentTime(byte &sec, byte &min, byte &hour,
                        byte &day, byte &mon, byte &year);
};

#endif