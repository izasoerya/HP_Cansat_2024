#ifndef TELEMETRY_H
#define TELEMETRY_H

struct Command
{
    bool sendReading;
    bool referenceCalibration;
    bool timeConversion;
    bool setActivate;
    bool setEnable;
    bool reset;
    bool manualBuzzer;
    bool manualServo;
    bool setBuzzer;
    uint16_t degree;
    String echo;
};

class Telemetry
{
private:
    const uint16_t teamID = 1084;
    int readGCSLength;
    String* finalResult;
    char* tempReadGCS;
    byte Counter, wordCounter = 0;
    Command GCS;

public:
    Telemetry();
    
    void parseInput(String receiveGCS);
    void listCommand(String finalString);
    String constructMessage(byte hour, byte minute, byte second,
                            uint16_t packetCount,
                            char mode, String getState, float altitudeBMP,
                            char HS_DEPLOYED, char PC_DEPLOYED, char MAST_RAISED,
                            float temperature, float batt, float pressure,
                            byte hour_ms, byte minute_ms, byte second_ms,
                            float altitudeGPS, float latitude, float longitude,
                            byte satCount, float angleX, float angleY, String echo
                            );
    

};

class FlightState 
{
private : 
    Command GCS;
    
public :
    FlightState();
    void beginServoBuzzer();
    String getState(byte State);
    void detectState(float altitudeBMP, float prevAltitude, byte State, bool logState[]);
};

#endif