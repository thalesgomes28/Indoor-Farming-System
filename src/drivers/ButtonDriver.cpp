// ======================================
// File: src/drivers/ButtonDriver.cpp
// ======================================

#include "drivers/ButtonDriver.h"

ButtonDriver::ButtonDriver(int pin)
{
    this->pin = pin;
    lastReading = HIGH;
    debouncedState = HIGH;
    pressEvent = false;
    debounceTimer = 0;
}

void ButtonDriver::begin()
{
    // Pullup interno: botão conecta pino ao GND → LOW = pressionado
    pinMode(pin, INPUT_PULLUP);
}

void ButtonDriver::update()
{
    bool reading = digitalRead(pin);

    if (reading != lastReading)
    {
        debounceTimer = millis();
    }

    if (millis() - debounceTimer >= DEBOUNCE_MS)
    {
        if (reading != debouncedState)
        {
            debouncedState = reading;

            if (debouncedState == LOW)
            {
                pressEvent = true;
            }
        }
    }

    lastReading = reading;
}

bool ButtonDriver::wasPressed()
{
    if (pressEvent)
    {
        pressEvent = false;
        return true;
    }
    return false;
}
