#include <Arduino.h>
#include <TeensyThreads.h>

#include "BMP.h"
#include "MPU6050.h"
#include "GPS.h"
#include "Telemetry.h"
#include "Component.h"
#include "Var.h"

SensorBMP bmp;
SensorMPU mpu(Wire);
SensorGPS gps;
Telemetry tele;

void SensorRead();
void ParseTelemetry();
void SendTelemetry();

void setup() {
  Serial.begin(9600);

  bmp.begin() ? Serial.println("BMP RUN") : Serial.println("Error BMP"); 
  mpu.begin() ? Serial.println("MPU RUN") : Serial.println("Error MPU");

  bmp.throwFirstReading(temperature);
  bmp.getReferencePressure(referencePressure);

  threads.addThread(SensorRead);
  threads.addThread(SendTelemetry);
}

void SensorRead()
{
  mpu.Calibrate();
  mpu.getCurrentData(angleX, angleY);
  
  bmp.getCurrentData(temperature, pressure); 
  bmp.getAltitudeFlight(altitudeBMP, referencePressure);
  //bmp.getAltitudeEEPROM(altitudeBMP, referencePressure);    Uncomment if want to use EEPROM
  bmp.getAltitudeSimulation(altitudeBMP, inputPressure);
  
  gps.getCurrentTime(second, minute, hour, date, month, year);
  gps.getCurrentLocation(latitude, longitude, altitudeGPS);
  gps.getCurrentSatelite(satCount);
}

void SendTelemetry() 
{

  telemetryData = tele.constructMessage(hour, minute, second,
                                        packetCount, 
                                        currentMode, tele.getState(State), altitudeBMP, 
                                        HS, PP, FB, 
                                        temperature, batt, pressure, 
                                        hour, minute, second, 
                                        altitudeGPS, latitude, longitude, 
                                        satCount, angleX, angleY, echo);
  Serial.print(telemetryData);

}

void loop() {
  // put your main code here, to run repeatedly:

}

