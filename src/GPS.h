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
    float getLatitude();
    float getLongitude();
    float getAltitudeGPS();
    byte getSatCount();
    void getCurrentTime(byte &sec, byte &min, byte &hour,
                        byte &day, byte &mon, byte &year);
    void getCurrentLocation(float &latitude, float &longitude, float &altitudeGPS);
    void getCurrentSatelite(byte &sateliteCount);
};

#endif