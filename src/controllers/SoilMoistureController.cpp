// ======================================
// File: src/controllers/SoilMoistureController.cpp
// ======================================

#include "controllers/SoilMoistureController.h"
#include "drivers/WaterPumpDriver.h"
#include "utils/Debug.h"


SoilMoistureController::SoilMoistureController(
    int pin,
    int threshold,
    int pumpControlPin
)
{
    sensorPin = pin;

    dryThreshold = threshold;

    waterPump = new WaterPumpDriver(pumpControlPin);
}

void SoilMoistureController::begin()
{
    pinMode(sensorPin, INPUT);
    waterPump->begin();
}

void SoilMoistureController::update()
{
    int sensorValue = analogRead(sensorPin);

    DEBUG_PRINTLN("[SOIL] VALUE: ");
    DEBUG_PRINTLN(sensorValue);

    // Acima de 900 = molhado
    // Abaixo de 900 = seco

    if (sensorValue < dryThreshold)
    {
        DEBUG_PRINTLN("[SOIL] DRY");

        if (!waterPump->isRunning())
        {
            waterPump->start();
        }
    }
    else
    {
        DEBUG_PRINTLN("[SOIL] WET");
        waterPump->stop();
    }

    waterPump->update();
}