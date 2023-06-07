#include <Arduino.h>
#include <TeensyThreads.h>

#include "BMP.h"
#include "MPU6050.h"
#include "GPS.h"
#include "Telemetry.h"
#include "Component.h"

SensorBMP bmp;
SensorMPU mpu(Wire);
SensorGPS gps;

void sensorRead();
void parseTelemetry();
void sendTelemetry();

float angleX, angleY, Gforce, prevGForce;
byte errorValueMPU;

float temperature, pressure, altitude, prevAltitude;
float simulationAltitude;
float referencePressure;
byte errorValueBMP;

byte sec, minute, hour;
byte date, month, year;
float latitude, longitude, altitudeGPS, satCount;

void setup() {
  Serial.begin(9600);
  while (!bmp.begin())
  {
    Serial.println("Error initialize MPU");
    bmp.begin();
  }
  while (!mpu.begin())
  {
    Serial.println("Error initialize MPU");
    mpu.begin(); 
  }
  bmp.throwFirstReading();
  referencePressure = bmp.getPressure();

  threads.addThread(sensorRead);
}

void sensorRead()
{
  mpu.Calibrate();
  
  angleX = mpu.getAngleX();
  angleY = mpu.getAngleY();

  temperature = bmp.getTemperature();
  pressure = bmp.getPressure();
  altitude = bmp.getAltitudeFlight(referencePressure);

}

void loop() {
  // put your main code here, to run repeatedly:
}

