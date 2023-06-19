#include <Arduino.h>

/* MPU VAR */
float *angleX, *angleY, *Gforce, *prevGForce;
byte errorValueMPU;

/* BMP VAR */
float *temperature, *pressure, *altitudeBMP, *prevAltitude;
float simulationAltitude;
float referencePressure;
byte errorValueBMP;

/* GPS VAR */
byte *second, *minute, *hour;
byte *date, *month, *year;
float *latitude, *longitude, *altitudeGPS; 
byte *satCount;

/* BATT VAR */
float batt;

/* FSW VAR */
char HS, PP, FB, currentMode;
byte State;

/* TELEMETRY VAR*/
uint32_t packetCount;
String echo, telemetryData;
char buffer[256];