#ifndef PART_H
#define PART_H

#include <Servo.h>

class MotorServo
{
private:
    Servo myservo;
public:
    MotorServo();
    void begin();
    void stateServo(uint16_t degree);
};

class Buzzer
{
private:
    
public:
    Buzzer();
    void begin();
    void stateBuzzer(bool state);
};


#endif