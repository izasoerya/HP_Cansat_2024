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

  bmp.throwFirstReading();
  referencePressure = bmp.getPressure();

  threads.addThread(SensorRead);
  threads.addThread(SendTelemetry);
}

void SensorRead()
{
  angleX = new float;
  angleY = new float;

  
  mpu.Calibrate();

  mpu.getAllData(*angleX, *angleY);
  bmp.getAllData(*temperature, *pressure, *altitudeBMP, referencePressure); 

  latitude    = gps.getLatitude();       //.7 Precision
  longitude   = gps.getLongitude();      //.7 Precision
  altitudeGPS = gps.getAltitudeGPS();
  satCount    = gps.getSatCount();
  second      = gps.getSecond();
  minute      = gps.getMinute();
  hour        = gps.getHour();
}

void SendTelemetry() 
{

  tele.constructMessage(hour, minute, second,
                        packetCount, 
                        currentMode, tele.getState(State), *altitudeBMP, 
                        HS, PP, FB, 
                        *temperature, batt, *pressure, 
                        hour, minute, second, 
                        altitudeGPS, latitude, longitude, 
                        satCount, *angleX, *angleY, echo, buffer);
}

void loop() {
  // put your main code here, to run repeatedly:

}

