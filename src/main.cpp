#include <Arduino.h>
#include <TeensyThreads.h>

#include "BMP.h"
#include "MPU6050.h"
#include "GPS.h"
#include "Telemetry.h"
#include "Component.h"
#include "Var.h"

SensorBMP BMP;
SensorMPU MPU(Wire);
SensorGPS GPS;
Telemetry TELE;
FlightState FSW;

void SensorRead();
void ParseTelemetry();
void SendTelemetry();

void setup() {
  Serial.begin(9600);

  BMP.begin() ? Serial.println("BMP RUN") : Serial.println("Error BMP"); 
  MPU.begin() ? Serial.println("MPU RUN") : Serial.println("Error MPU");

  BMP.throwFirstReading(temperature);
  BMP.getReferencePressure(referencePressure);

  threads.addThread(SensorRead);
  threads.addThread(SendTelemetry);
}

void SensorRead()
{
  MPU.Calibrate();
  MPU.getCurrentData(angleX, angleY);
  
  BMP.getCurrentData(temperature, pressure);    //Pressure in Pascal
  BMP.getAltitudeFlight(altitudeBMP, referencePressure);    //Altitude in meter
  BMP.getAltitudeSimulation(altitudeBMP, inputPressure);    //Altitude in meter
  
  GPS.getCurrentTime(second, minute, hour, date, month, year);    
  GPS.getCurrentLocation(latitude, longitude, altitudeGPS);
  GPS.getCurrentSatelite(satCount);

  FSW.detectState(altitudeBMP, prevAltitude, State, logState);
}

void SendTelemetry() 
{

  telemetryData = TELE.constructMessage(hour, minute, second,
                                        packetCount, 
                                        currentMode, FSW.getState(State), altitudeBMP, 
                                        HS, PP, FB, 
                                        temperature, batt, pressure, 
                                        hour, minute, second, 
                                        altitudeGPS, latitude, longitude, 
                                        satCount, angleX, angleY, echo);
  Serial.print(telemetryData);

}

void ParseTelemetry() 
{
  String hasilSerial;
  hasilSerial = "";
  while(Serial2.available() > 0)
  {
    hasilSerial += (char)Serial2.read();
  }
  hasilSerial.trim();
}

void loop() {
  // put your main code here, to run repeatedly:

}

