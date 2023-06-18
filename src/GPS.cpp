#include <Arduino.h>
#include "GPS.h"

SensorGPS::SensorGPS() : gps(), fix() {}

void SensorGPS::Calibrate() {
    while (gps.available(Serial3) > 0) {
        fix = gps.read();
    }
}

float SensorGPS::getLatitude() {
    if (fix.valid.location) {
        return fix.latitude();
    }
    else {
        return 254;
    }
}

float SensorGPS::getLongitude() {
    if (fix.valid.location) {
        return fix.longitude();
    }
    else {
        return 254;
    }
}

float SensorGPS::getAltitudeGPS() {
    if (fix.valid.altitude) {
        return fix.altitude();
    }
    else {
        return 254;
    }
}

byte SensorGPS::getSatCount() {
    if (fix.valid.satellites) {
        return fix.satellites;
    }
    else {
        return 254;
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
    if (fix.valid.date)
    {
        day = fix.dateTime.date;
        mon = fix.dateTime.month;
        year = fix.dateTime.year;
    }

}