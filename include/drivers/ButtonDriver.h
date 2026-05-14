// ======================================
// File: include/drivers/ButtonDriver.h
// ======================================

#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H

#include <Arduino.h>

class ButtonDriver
{
private:
    int pin;
    bool lastReading;
    bool debouncedState;
    bool pressEvent;
    unsigned long debounceTimer;

    static const unsigned long DEBOUNCE_MS = 50;

public:
    ButtonDriver(int pin);

    void begin();
    void update();

    bool wasPressed();
};

#endif
