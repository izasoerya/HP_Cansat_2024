#ifndef BMP388_H
#define BMP388_H

#include <EEPROM.h>
#include "Adafruit_BMP3XX.h"

class SensorBMP {
private:
    Adafruit_BMP3XX bmp;
    struct kalmanVar {
      float Estimate = 0;
      float ErrorEstimate = 0.3;
      float Gain;
      float Measurement;
    };
    float ePressure;
public:
    SensorBMP();

    bool begin();
    void throwFirstReading(float &temp);
    void getReferencePressure(float &referencePressure);
    
    void getCurrentData(float &temp, float &press);
    void getAltitudeFlight(float &altitudeFlight, float referencePressure);
    void getAltitudeSimulation(float &altitudeSimulation, float inputPressure);

    void getAltitudeEEPROM(float &altitudeBMP, float referencePressure);
    byte cError();
};

#endif