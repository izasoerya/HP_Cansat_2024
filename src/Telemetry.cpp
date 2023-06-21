#include <Arduino.h>
#include "Telemetry.h"

Telemetry::Telemetry(){}

FlightState::FlightState(){}

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

String FlightState::getState(byte State)
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

void FlightState::detectState(float altitudeBMP, float prevAltitude, byte State, bool logState[])
{
    if (altitudeBMP < 5 && logState[2] == false)
    {
        State = 0; logState[0] = true;  
    }
    else if (altitudeBMP >= 5 && logState[2] == false) 
    {
        State = 1; logState[1] = true;
    }
    else if (altitudeBMP > prevAltitude + 1 && logState[1] == true && logState[3] == false)
    {
        State = 2; logState[2] = true;
    }
    else if (altitudeBMP > 500 && altitudeBMP <= 600 && logState[2] == true)
    {
        State = 3; logState[3] = true;
    }
    else if (altitudeBMP > 200 && altitudeBMP <= 500 && logState[3] == true)
    {
        State = 4; logState[4] = true;
    }
    else if (altitudeBMP > 10 && altitudeBMP <= 200 && logState[4] == true)
    {
        State = 5; logState[5] = true;
    }
    else if (altitudeBMP <= 10 && logState[5] == true)
    {
        State = 6; logState[6] = true;
    }
    else 
    {
        State = -1;
    }
}

/*  TELEMETRY  */

String Telemetry::parseInput(String receiveGCS)
{
    readGCSLength = receiveGCS.length();
    tempReadGCS = new char[readGCSLength+1];
    finalResult = new String[readGCSLength+1];    
    
    strcpy(tempReadGCS, receiveGCS.c_str());
    for (Counter = 0; Counter < receiveGCS.length(); Counter++)
    {
        if (tempReadGCS[Counter] != ',')
        {
            finalResult[wordCounter] += tempReadGCS[Counter];
            finalResult[wordCounter].trim();
        }
        else
        {
            wordCounter++;
        }
    }
    return *finalResult;
}

void Telemetry::listCommand(String finalString)
{
    Command comm;
    if (finalString == "CMD1084CXON")
    {
        comm.sendReading = true;
    }
    
}

String Telemetry::constructMessage( byte hour, byte minute, byte second,
                                    float packetCount,
                                    char mode, String getState, float altitudeBMP,
                                    char HS_DEPLOYED, char PC_DEPLOYED, char MAST_RAISED,
                                    float temperature, float batt, float pressure,
                                    byte hour_ms, byte minute_ms, byte second_ms,
                                    float altitudeGPS, float latitude, float longitude,
                                    byte satCount, float angleX, float angleY, String echo
                                    ) 
{
    char buffer[256];
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