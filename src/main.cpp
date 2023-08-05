#include <Arduino.h>
#include <TeensyThreads.h>

#include "BMP.h"
#include "MPU6050.h"
#include "GPS.h"
#include "Telemetry.h"
#include "Var.h"

SensorBMP BMP;
SensorMPU MPU(Wire);
SensorGPS GPS;
Telemetry TELE;
FlightState FSW;
Command COMM;

void SensorRead();
void ParseTelemetry();
void SendTelemetry();

void setup() {
	Serial.begin(9600);
	FSW.beginServoBuzzer();

	BMP.begin() ? Serial.println("BMP RUN") : Serial.println("Error BMP"); 
	MPU.begin() ? Serial.println("MPU RUN") : Serial.println("Error MPU");

	BMP.throwFirstReading(temperature);
	BMP.getReferencePressure(referencePressure);

	threads.addThread(SensorRead);
	threads.addThread(SendTelemetry);
	threads.addThread(ParseTelemetry);
}

void SensorRead()
{
	while(1)
	{
		MPU.Calibrate() ? MPU.setData(angleX, angleY, angleZ) : MPU.setZero(angleX, angleY, angleZ); 

		BMP.getCurrentData(temperature, pressure);    //Pressure in Pascal
		BMP.getAltitudeFlight(altitudeBMP, referencePressure);    
		BMP.getAltitudeSimulation(altitudeBMP, inputPressure);    

		GPS.getCurrentTime(second, minute, hour, date, month, year);    
		GPS.getCurrentLocation(latitude, longitude, altitudeGPS);
		GPS.getCurrentSatelite(satCount);

		FSW.detectState(altitudeBMP, prevAltitude, State, logState);
	}
}

void SendTelemetry() 
{
	while(1)
	{
		telemetryData = TELE.constructMessage(hour, minute, second,
											packetCount, 
											currentMode, FSW.getState(State), altitudeBMP, 
											HS, PP, FB, 
											temperature, batt, pressure, 
											hour, minute, second, 
											altitudeGPS, latitude, longitude, 
											satCount, angleX, angleY, COMM.echo);
		Serial.print(telemetryData);
	}
}

void ParseTelemetry() 
{
	while(1)
	{
		hasilSerial = "";
		while(Serial2.available() > 0)
		{
		hasilSerial += (char)Serial2.read();
		}
		TELE.parseInput(hasilSerial);
	}
}

void loop() {
  // put your main code here, to run repeatedly:

}

