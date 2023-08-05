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
    bool Calibrate();
    void setData(float &rot_x, float &rot_y, float &rot_z);
    void setZero(float &rot_x, float &rot_y, float &rot_z);
    byte status();
};


#endif