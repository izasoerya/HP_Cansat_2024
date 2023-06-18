#include <Arduino.h>
#include "MPU6050.h"

SensorMPU::SensorMPU(TwoWire I2C):mpu(MPU6050(Wire)) {}


bool SensorMPU::begin() 
{
    Wire.begin();
    if (!mpu.begin()) 
    {
        return false;
    }
    else 
    {
        mpu.calcOffsets(true,true);
        return true;
    }
}

void SensorMPU::Calibrate() 
{
    mpu.update();
}

byte SensorMPU::cError() 
{
    Wire.beginTransmission(0x66);
    return Wire.endTransmission();
}

void SensorMPU::getAllData(float &angleX, float &angleY)
{
    angleX = mpu.getAngleX();
    angleY = mpu.getAngleY();
}