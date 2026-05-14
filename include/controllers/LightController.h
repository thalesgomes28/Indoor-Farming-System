// ===========================
// File: LightController.h
// ===========================

#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include <Arduino.h>
#include "drivers/ButtonDriver.h"
#include "drivers/LightPersistenceDriver.h"

class LightController
{
private:
    int outputPin;

    unsigned long onTime;
    unsigned long offTime;

    bool lightOn;
    unsigned long lastChange;
    uint16_t hoursElapsed;

    ButtonDriver button;
    LightPersistenceDriver persistence;

    void resetCycle(bool newLightOn);

public:
    LightController(int outputPin,
                    int buttonPin,
                    unsigned long onDuration,
                    unsigned long offDuration);

    void begin();
    void update();
};

#endif
