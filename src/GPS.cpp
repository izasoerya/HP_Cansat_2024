#include <Arduino.h>
#include "GPS.h"

SensorGPS::SensorGPS() : gps(), fix() {}

void SensorGPS::Calibrate() {
    while (gps.available(Serial3) > 0) {
        fix = gps.read();
    }
}

byte SensorGPS::getDate() {
    if (fix.valid.date) {
        return fix.dateTime.date;
    }
    else {
        return 254;
    }
}

byte SensorGPS::getMonth() {
    if (fix.valid.date) {
        return fix.dateTime.month;
    }
    else {
        return 254;
    }
}

byte SensorGPS::getYear() {
    if (fix.valid.date) {
        return fix.dateTime.year;
    }
    else {
        return 254;
    }

}

byte SensorGPS::getSecond() {
    if (fix.valid.time) {
        return fix.dateTime.seconds;
    }
    else {
        return 254;
    }

}

byte SensorGPS::getMinute() {
    if (fix.valid.time) {
        return fix.dateTime.minutes;
    }
    else {
        return 254;
    }

}

byte SensorGPS::getHour() {
    if (fix.valid.time) {
        return fix.dateTime.hours;
    }
    else {
        return 254;
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