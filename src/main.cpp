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

const int LIGHT_OUTPUT_PIN = 5;
const int LIGHT_BUTTON_PIN = 10;

const int SOIL_MOISTURE_SENSOR_PIN = A0;
const int SOIL_MOISTURE_DRY_THRESHOLD = 900;
const int WATER_PUMP_CONTROL_PIN = 4;

// Instâncias
LightController lightController(
    LIGHT_OUTPUT_PIN,
    LIGHT_BUTTON_PIN,
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

static unsigned long lastSlowUpdate = 0;

void loop()
{
    // LightController roda a cada iteração para que o botão
    // seja amostrado em ~1 ms — necessário para o debounce funcionar.
    lightController.update();

    // Demais controllers rodam a cada 1 s para não spammar serial
    // com leituras de sensor e não desperdiçar ciclos de CPU.
    if (millis() - lastSlowUpdate >= 1000UL)
    {
        lastSlowUpdate += 1000UL;

        temperatureController.update();
        humidityController.update();
        soilMoistureController.update();
    }
}