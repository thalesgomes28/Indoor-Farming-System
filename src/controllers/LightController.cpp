// ===========================
// File: LightController.cpp
// ===========================

#include "controllers/LightController.h"
#include "utils/Debug.h"

LightController::LightController(int pin,
                                 unsigned long onDuration,
                                 unsigned long offDuration)
{
    outputPin = pin;
    onTime = onDuration;
    offTime = offDuration;

    state = false;
    lastChange = 0;
}

void LightController::begin()
{
    DEBUG_PRINTLN("[LIGHT] iniciado");
    pinMode(outputPin, OUTPUT);
}

void LightController::update()
{
    unsigned long currentMillis = millis();

    if (state)
    {
        digitalWrite(outputPin, LOW);

        if (currentMillis - lastChange >= onTime)
        {
            state = false;
            lastChange = currentMillis;

            DEBUG_PRINTLN("[LIGHT] OFF");
        }
    }
    else
    {
        digitalWrite(outputPin, HIGH);

        if (currentMillis - lastChange >= offTime)
        {
            state = true;
            lastChange = currentMillis;

            DEBUG_PRINTLN("[LIGHT] ON");
        }
    }
}