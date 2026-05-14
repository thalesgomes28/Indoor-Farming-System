// ======================================
// File: include/controllers/SoilMoistureController.h
// ======================================

#ifndef SOIL_MOISTURE_CONTROLLER_H
#define SOIL_MOISTURE_CONTROLLER_H

#include <Arduino.h>
#include "drivers/WaterPumpDriver.h"

class SoilMoistureController
{
private:
    int sensorPin;

    int dryThreshold;

    WaterPumpDriver* waterPump;

public:
    SoilMoistureController(
        int pin,
        int threshold,
        int pumpControlPin
    );

    void begin();

    void update();
};

#endif