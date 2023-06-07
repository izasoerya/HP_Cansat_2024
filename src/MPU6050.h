#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>
#include <MPU6050_light.h>

class SensorMPU
{
private:
    MPU6050 mpu;
    
public:
    SensorMPU(TwoWire I2C);
    bool begin();
    void Calibrate();
    float getAngleX();
    float getAngleY();

};


#endif