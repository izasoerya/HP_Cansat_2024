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


float SensorBMP::getAltitudeSimulation(float inputPressure)        //   inputPressure is in Pascal (Pa)
{
    return bmp.readAltitude(inputPressure/100.0F);
}

float SensorBMP::getAltitudeEEPROM(float referencePressure)     
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
    return ePressure;
}

void SensorBMP::throwFirstReading() 
{
    while (bmp.temperature < 23) 
    {
        bmp.temperature;
    }
}

byte SensorBMP::cError() 
{
    Wire.beginTransmission(0x77);
    return Wire.endTransmission();
}

void SensorBMP::getCurrentData(float &temp, float &press, float &altit, float referencePressure)
{
    kalmanVar kalman;
    temp = bmp.temperature;
    press = bmp.pressure;
    kalman.Gain = kalman.ErrorEstimate / (kalman.ErrorEstimate + 0.5);
    altit = kalman.Estimate + kalman.Gain * (bmp.readAltitude(referencePressure/100.0F) - kalman.Estimate);
    kalman.ErrorEstimate = (0.5 - kalman.Gain) * kalman.ErrorEstimate;
}