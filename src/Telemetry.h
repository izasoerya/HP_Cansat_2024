#ifndef TELEMETRY_H
#define TELEMETRY_H

class Telemetry
{
private:
    const uint16_t teamID = 1084;

public:
    Telemetry();
    String getState(byte State);
    String constructMessage(float hour, float minute, float second,
                            float packetCount,
                            char mode, String getState, float altitudeBMP,
                            char HS_DEPLOYED, char PC_DEPLOYED, char MAST_RAISED,
                            float temperature, float batt, float pressure,
                            float hour_ms, float minute_ms, float second_ms,
                            float altitudeGPS, float latitude, float longitude,
                            byte satCount, float angleX, float angleY, String echo,
                            char buffer[256]
                            );


};


#endif