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


  threads.addThread(SensorRead);
  threads.addThread(SendTelemetry);
}

void allocateMemory() 
{
  angleX = new float;   angleY = new float;
  temperature = new float;  pressure = new float;   altitudeBMP = new float;
  second = new byte; minute = new byte; hour = new byte;
  date = new byte; month = new byte; year = new byte;
  latitude = new float; longitude = new float; altitudeGPS = new float; satCount = new byte;
}

void deallocateMemory() 
{
  delete angleX;  delete angleY;
  delete temperature; delete pressure; delete altitudeBMP;
  delete second; delete minute; delete year;
  delete date; delete month; delete year;
  delete latitude; delete longitude; delete altitudeGPS; delete satCount;
}

void SensorRead()
{
  allocateMemory();
  
  mpu.Calibrate();
  mpu.getCurrentData    (*angleX, *angleY);
  
  bmp.getCurrentData    (*temperature, *pressure, *altitudeBMP, referencePressure); 
  
  gps.getCurrentTime    (*second, *minute, *hour, *date, *month, *year);
  gps.getCurrentLocation(*latitude, *longitude, *altitudeGPS);
  gps.getCurrentSatelite(*satCount);


}

void SendTelemetry() 
{

  telemetryData = tele.constructMessage(*hour, *minute, *second,
                                        packetCount, 
                                        currentMode, tele.getState(State), *altitudeBMP, 
                                        HS, PP, FB, 
                                        *temperature, batt, *pressure, 
                                        *hour, *minute, *second, 
                                        *altitudeGPS, *latitude, *longitude, 
                                        *satCount, *angleX, *angleY, echo, buffer);
  Serial.print(telemetryData);
  deallocateMemory();
}

void loop() {
  // put your main code here, to run repeatedly:

}

