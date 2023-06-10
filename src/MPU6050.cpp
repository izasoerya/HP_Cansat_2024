#include <Arduino.h>
#include "MPU6050.h"
#include <KalmanFilter.h>

SensorMPU::SensorMPU(TwoWire I2C):mpu(MPU6050(Wire)) {}

KalmanFilter kalmanX(0.001, 0.003, 0.03);
KalmanFilter kalmanY(0.001, 0.003, 0.03);

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

float SensorMPU::getAngleX()
{   
    return kalmanX.update(mpu.getAngleX(), mpu.getGyroX());
}

float SensorMPU::getAngleY()
{
    return kalmanX.update(mpu.getAngleY(), mpu.getGyroY());
}

byte SensorMPU::cError() 
{
    Wire.beginTransmission(0x66);
    return Wire.endTransmission();
}