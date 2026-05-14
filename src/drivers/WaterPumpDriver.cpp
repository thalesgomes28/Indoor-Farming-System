// ======================================
// File: src/drivers/WaterPumpDriver.cpp
// ======================================

#include "drivers/WaterPumpDriver.h"

WaterPumpDriver::WaterPumpDriver(int pin)
{
    controlPin = pin;
    running = false;
    startTime = 0;
}

void WaterPumpDriver::begin()
{
    pinMode(controlPin, OUTPUT);

    digitalWrite(controlPin, LOW);
}

void WaterPumpDriver::start()
{
    if (!running)
    {
        running = true;

        startTime = millis();

        digitalWrite(controlPin, HIGH);

        Serial.println("[PUMP] ON");
    }
}

void WaterPumpDriver::stop()
{
            running = false;

            digitalWrite(controlPin, LOW);

            Serial.println("[PUMP] OFF");
}

void WaterPumpDriver::update()
{
    if (running)
    {
        if (millis() - startTime >= RUN_TIME)
        {
            stop();
        }
    }
}

bool WaterPumpDriver::isRunning()
{
    return running;
}