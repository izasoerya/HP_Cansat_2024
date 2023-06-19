#include <Arduino.h>
#include "GPS.h"

SensorGPS::SensorGPS() : gps(), fix() {}

void SensorGPS::Calibrate() {
    while (gps.available(Serial3) > 0) {
        fix = gps.read();
    }
}

void SensorGPS::getCurrentTime( byte &sec, byte &min, byte &hour,
                                byte &day, byte &mon, byte &year)
{
    if (fix.valid.time) 
    {
        sec = fix.dateTime.seconds;
        min = fix.dateTime.minutes;
        hour = fix.dateTime.hours;
    }
    else
    {
        sec = 0; min = 0; hour = 0;
    }
    if (fix.valid.date)
    {
        day = fix.dateTime.date;
        mon = fix.dateTime.month;
        year = fix.dateTime.year;
    }
    else
    {
        day = 0; mon = 0; year = 0;
    }
}

void SensorGPS::getCurrentLocation(float &latitude, float &longitude, float &altitudeGPS)
{
    if (fix.valid.location)
    {
        latitude = fix.latitude();
        longitude = fix.longitude();
    }
    if (fix.valid.altitude)
    {
        altitudeGPS = fix.altitude();
    }
}

void SensorGPS::getCurrentSatelite(byte &sateliteCount)
{
    if (fix.valid.satellites) 
    {
        sateliteCount = fix.satellites;
    }
}



