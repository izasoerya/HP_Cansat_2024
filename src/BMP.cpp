#include <Arduino.h>
#include "BMP.h"

SensorBMP::SensorBMP():bmp(Adafruit_BMP3XX()){}

bool SensorBMP::begin() 
{
    if (!bmp.begin_I2C()) 
    {
        return false;
    }
    else
    {
        bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
        bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
        bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
        bmp.setOutputDataRate(BMP3_ODR_50_HZ);
        return true;        
    }
}

void SensorBMP::getReferencePressure(float &referencePressure)
{
    referencePressure = bmp.pressure;
}


void SensorBMP::getCurrentData(float &temp, float &press)
{
    temp = bmp.temperature;
    press = bmp.pressure;
}

void SensorBMP::getAltitudeFlight(float &altitudeFlight, float referencePressure)
{
    kalmanVar kalman;
    kalman.Gain = kalman.ErrorEstimate / (kalman.ErrorEstimate + 0.5);
    altitudeFlight = kalman.Estimate + kalman.Gain * (bmp.readAltitude(referencePressure/100.0F) - kalman.Estimate);
    kalman.ErrorEstimate = (0.5 - kalman.Gain) * kalman.ErrorEstimate;
}

void SensorBMP::getAltitudeSimulation(float &altitudeSimulation, float inputPressure)        //   inputPressure is in Pascal (Pa)
{
    altitudeSimulation = bmp.readAltitude(inputPressure/100.0F);
}

void SensorBMP::getAltitudeEEPROM(float &altitudeBMP, float referencePressure)     
{
    kalmanVar kalman;
    if(EEPROM.read(11) == 255)
    {
        //ePressure = referencePressure;            //  Uncomment if want to use current reference presssure
        ePressure = bmp.temperature;       //  Read new pressure to store and used as reference
        EEPROM.put(11, ePressure);                  
    }
    else 
    {
        EEPROM.get(11, ePressure);
    }
    altitudeBMP = bmp.readAltitude(ePressure);
}

void SensorBMP::throwFirstReading(float &temp) 
{
    while (bmp.temperature < 23) 
    {
        temp = bmp.temperature;
    }
}

byte SensorBMP::cError() 
{
    Wire.beginTransmission(0x77);
    return Wire.endTransmission();
}
