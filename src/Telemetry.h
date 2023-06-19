#ifndef TELEMETRY_H
#define TELEMETRY_H

class Telemetry
{
private:
    const uint16_t teamID = 1084;

public:
    Telemetry();
    String getState(byte State);
    byte detectState(float altitudeBMP, float prevAltitude, byte State, bool logState[]);
    String constructMessage(byte hour, byte minute, byte second,
                            float packetCount,
                            char mode, String getState, float altitudeBMP,
                            char HS_DEPLOYED, char PC_DEPLOYED, char MAST_RAISED,
                            float temperature, float batt, float pressure,
                            byte hour_ms, byte minute_ms, byte second_ms,
                            float altitudeGPS, float latitude, float longitude,
                            byte satCount, float angleX, float angleY, String echo
                            );


};


#endif