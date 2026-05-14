// ===========================
// File: LightController.cpp
// ===========================

#include "controllers/LightController.h"
#include "utils/Debug.h"

LightController::LightController(int outputPin,
                                 int buttonPin,
                                 unsigned long onDuration,
                                 unsigned long offDuration)
    : button(buttonPin)
{
    this->outputPin = outputPin;
    onTime = onDuration;
    offTime = offDuration;
    lightOn = true;
    lastChange = 0;
    hoursElapsed = 0;
}

void LightController::begin()
{
    pinMode(outputPin, OUTPUT);
    button.begin();
    persistence.begin();

    if (persistence.hasValidData())
    {
        persistence.load(lightOn, hoursElapsed);

        // Recua o lastChange para que o timer "retome" do ponto salvo.
        // A aritmética unsigned lida corretamente com o underflow.
        lastChange = millis() - (unsigned long)hoursElapsed * 3600000UL;

        DEBUG_PRINTLN("[LIGHT] Estado restaurado do EEPROM");
    }
    else
    {
        lightOn = true;
        hoursElapsed = 0;
        lastChange = millis();
        persistence.save(lightOn, hoursElapsed);
    }

    digitalWrite(outputPin, lightOn ? HIGH : LOW);

    DEBUG_PRINTLN(lightOn ? "[LIGHT] ON" : "[LIGHT] OFF");
}

void LightController::update()
{
    button.update();

    if (button.wasPressed())
    {
        DEBUG_PRINTLN("[LIGHT] Botao - toggle manual");
        resetCycle(!lightOn);
        return;
    }

    unsigned long elapsed = millis() - lastChange;
    unsigned long phaseDuration = lightOn ? onTime : offTime;

    if (elapsed >= phaseDuration)
    {
        resetCycle(!lightOn);
        return;
    }

    // Incrementa contador de horas a cada hora completa na fase atual
    unsigned long nextHourMs = (unsigned long)(hoursElapsed + 1) * 3600000UL;
    if (elapsed >= nextHourMs)
    {
        hoursElapsed++;
        persistence.save(lightOn, hoursElapsed);

        DEBUG_PRINT("[LIGHT] Horas na fase atual: ");
        DEBUG_PRINTLN(hoursElapsed);
    }
}

void LightController::resetCycle(bool newLightOn)
{
    lightOn = newLightOn;
    hoursElapsed = 0;
    lastChange = millis();
    persistence.save(lightOn, hoursElapsed);
    digitalWrite(outputPin, lightOn ? HIGH : LOW);

    DEBUG_PRINTLN(lightOn ? "[LIGHT] ON" : "[LIGHT] OFF");
}
