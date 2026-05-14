#include <Arduino.h>

#include "controllers/LightController.h"
#include "controllers/TemperatureController.h"
#include "controllers/HumidityController.h"
#include "controllers/SoilMoistureController.h"
#include "utils/Debug.h"

const unsigned long LIGHT_ON_TIME =
    16UL * 60UL * 60UL * 1000UL;

const unsigned long LIGHT_OFF_TIME =
    6UL * 60UL * 60UL * 1000UL;

const int SOIL_MOISTURE_SENSOR_PIN = A0;
const int SOIL_MOISTURE_DRY_THRESHOLD = 900;
const int WATER_PUMP_CONTROL_PIN = 4;

// Instâncias
LightController lightController(
    5,
    LIGHT_ON_TIME,
    LIGHT_OFF_TIME);

TemperatureController temperatureController;
HumidityController humidityController;
SoilMoistureController soilMoistureController(
    SOIL_MOISTURE_SENSOR_PIN,
    SOIL_MOISTURE_DRY_THRESHOLD,
    WATER_PUMP_CONTROL_PIN
);

void setup()
{
    Serial.begin(9600);

    while (!Serial)
    {
        ;
    }    

    DEBUG_PRINTLN("Sistema iniciando...");

    lightController.begin();
    temperatureController.begin();
    humidityController.begin();
    soilMoistureController.begin();
}

void loop()
{
    lightController.update();

    temperatureController.update();

    humidityController.update();

    soilMoistureController.update();

    delay(1000);
}