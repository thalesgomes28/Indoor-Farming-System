// ===========================
// File: LightController.h
// ===========================

#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include <Arduino.h>

class LightController
{
private:
    int outputPin;

    unsigned long onTime;
    unsigned long offTime;

    bool state;
    unsigned long lastChange;

public:
    LightController(int pin,
                    unsigned long onDuration,
                    unsigned long offDuration);

    void begin();
    void update();
};

#endif