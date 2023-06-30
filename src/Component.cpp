#include <Arduino.h>
#include "Component.h"

#define PIN_SERVO 2
#define PIN_BUZZER 3

MotorServo::MotorServo():myservo(Servo()){}

void MotorServo::begin()
{
    pinMode(PIN_SERVO, OUTPUT);
    myservo.write(0);
}

void MotorServo::stateServo(uint16_t degree)
{
    myservo.write(degree);
}

Buzzer::Buzzer(){}

void Buzzer::begin()
{
    pinMode(PIN_BUZZER, OUTPUT);
}

void Buzzer::stateBuzzer(bool state) 
{
    digitalWrite(PIN_BUZZER, state);
}