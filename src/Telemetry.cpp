#include <Arduino.h>
#include "Telemetry.h"
#include "Component.h"

MotorServo Servo;
Buzzer Buzz;

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

void FlightState::beginServoBuzzer()
{
    Servo.begin();
    Buzz.begin();
}

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
        State = 0; logState[0] = true;      //STANDBY
    }
    else if (altitudeBMP >= 5 && logState[2] == false) 
    {
        State = 1; logState[1] = true;      //ASCENT
    }
    else if (altitudeBMP > prevAltitude + 1 && logState[1] == true && logState[3] == false)
    {
        State = 2; logState[2] = true;      //SEPARATION
    }
    else if (altitudeBMP > 500 && altitudeBMP <= 600 && logState[2] == true)
    {
        State = 3; logState[3] = true;      //DESCENT
    }
    else if (altitudeBMP > 200 && altitudeBMP <= 500 && logState[3] == true)
    {
        State = 4; logState[4] = true;      //HS_RELEASE
        Servo.stateServo(30);
    }
    else if (altitudeBMP > 10 && altitudeBMP <= 200 && logState[4] == true)
    {
        State = 5; logState[5] = true;      //PP_RELEASE
        Servo.stateServo(60);
    }
    else if (altitudeBMP <= 10 && logState[5] == true)
    {
        State = 6; logState[6] = true;      //LANDING
        Servo.stateServo(90);
        GCS.manualBuzzer? Buzz.stateBuzzer(GCS.setBuzzer) : Buzz.stateBuzzer(HIGH);
    }
    else 
    {
        State = -1;
    }
}

/*  TELEMETRY  */

void Telemetry::parseInput(String receiveGCS)
{
    tempReadGCS = new char[receiveGCS.length() + 1];
    finalResult = new String[receiveGCS.length() + 1];    
    
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
    listCommand(String(finalResult[0]+finalResult[1]+finalResult[2]+finalResult[3]));
    delete[] tempReadGCS;
    delete[] finalResult;
}

void Telemetry::listCommand(String finalString)
{ 
    if (finalString == "CMD1084CXON")
    {
        GCS.sendReading = true;
        GCS.echo = "CXON";
    }
    if (finalString == "CMD1084CXOFF")
    {
        GCS.sendReading = false;
        GCS.echo = "CXOFF";
    }
    if (finalString == "CMD1084STGPS")
    {
        GCS.timeConversion = true;
        GCS.echo = "STGPS";
    }
    if (finalString == "CMD1084CAL")
    {
        GCS.referenceCalibration = true;
        GCS.echo = "CALL";
    }
    if (finalString == "CMD1084SIMACTIVATE")
    {
        GCS.setActivate = true;
        GCS.echo = "SIMACTIVATE";
    }
    if (finalString == "CMD1084SIMENABLE")
    {
        GCS.setEnable = true;
        GCS.echo = "SIMENABLE";
    }
    if (finalString == "CMD1084SIMDISABLE")
    {
        GCS.setActivate = false;
        GCS.setEnable = false;
        GCS.echo = "SIMDISABLE";
    }
    if (finalString == "CMD1084BUZZON")
    {
        GCS.manualBuzzer = true;
        GCS.setBuzzer = true;
        Buzz.stateBuzzer(HIGH);
        GCS.echo = "BUZZON";
    }
    if (finalString == "CMD1088BUZZOFF")
    {
        GCS.manualBuzzer = true;
        GCS.setBuzzer = false;
        Buzz.stateBuzzer(LOW);
        GCS.echo = "BUZZOFF";
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
                 mode, getState.c_str(), altitudeBMP,
                 HS_DEPLOYED, PC_DEPLOYED, MAST_RAISED,
                 temperature, batt, pressure,
                 hour, minute, second,
                 altitudeGPS, latitude, longitude,
                 satCount, angleX, angleY, echo.c_str());

    return String(buffer);
}