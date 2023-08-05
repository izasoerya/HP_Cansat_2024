#include <Arduino.h>
#include "MPU6050.h"

SensorMPU::SensorMPU(TwoWire I2C):mpu(MPU6050(Wire)) {}


bool SensorMPU::begin() 
{
    Wire.begin();
    byte status = mpu.begin();
    if (status != 0) return false;
    mpu.calcOffsets(true, true);
    return true;
}

bool SensorMPU::Calibrate() 
{
    byte condition = this->status();
    if (condition != 0) return false;
    mpu.update();
    return true;
}

byte SensorMPU::status() 
{
    Wire.beginTransmission(0x66);
    return Wire.endTransmission();
}

void SensorMPU::setData(float &rot_x, float &rot_y, float &rot_z)
{
    rot_x = mpu.getAngleX();
    rot_y = mpu.getAngleY();
    rot_z = mpu.getAngleZ();
}

void SensorMPU::setZero(float &rot_x, float &rot_y, float &rot_z)
{
    rot_x = 0;
    rot_y = 0;
    rot_z = 0;
}
