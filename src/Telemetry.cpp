#include <Arduino.h>
#include "Telemetry.h"

Telemetry::Telemetry(){}

enum State
{
    STANDBY = 0,
    ASCENT = 1,
    SEPARATION = 2,
    DESCENT = 3,
    HS_RELEASE = 4,
    PP_RELEASE = 5,
    LANDED = 6,
    INVALID = -1
};

String Telemetry::getState(byte State)
{
    switch (State) 
    {
        case STANDBY:
            return "STANDBY";
        case ASCENT:
            return "ASCENT";
        case SEPARATION:
            return "SEPARATION";
        case DESCENT:
            return "DESCENT";
        case HS_RELEASE:
            return "HS_RELEASE";
        case PP_RELEASE:
            return "PP_RELEASE";
        case LANDED:
            return "LANDED";
        default:
            return "INVALID";
    }
}

String Telemetry::constructMessage( byte hour, byte minute, byte second,
                                    float packetCount,
                                    char mode, String getState, float altitudeBMP,
                                    char HS_DEPLOYED, char PC_DEPLOYED, char MAST_RAISED,
                                    float temperature, float batt, float pressure,
                                    byte hour_ms, byte minute_ms, byte second_ms,
                                    float altitudeGPS, float latitude, float longitude,
                                    byte satCount, float angleX, float angleY, String echo,
                                    char buffer[256]
                                    ) 
{
    memset(buffer, 0, sizeof(buffer));
        snprintf(buffer, sizeof(buffer),
                 "%04d,"
                 "%02d:%02d:%02d,"
                 "%1d,"
                 "%c,%s,%.2f,"
                 "%c,%c,%c,"
                 "%.1f,%.2f,%.1f,"
                 "%02d:%02d:%02d,"
                 "%.2f,%.4f,%.4f,"
                 "%02d,%.2f,%.2f,%s\r",
                 teamID,
                 hour, minute, second,
                 packetCount,
                 mode, getState, altitudeBMP,
                 HS_DEPLOYED, PC_DEPLOYED, MAST_RAISED,
                 temperature, batt, pressure,
                 hour, minute, second,
                 altitudeGPS, latitude, longitude,
                 satCount, angleX, angleY, echo);

    return String(buffer);
}