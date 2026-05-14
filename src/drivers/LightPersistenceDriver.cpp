// ==========================================================
// File: src/drivers/LightPersistenceDriver.cpp
// ==========================================================

#include "drivers/LightPersistenceDriver.h"
#include <EEPROM.h>

void LightPersistenceDriver::begin()
{
    // EEPROM em AVR não requer inicialização de hardware
}

bool LightPersistenceDriver::hasValidData()
{
    return EEPROM.read(BASE_ADDR) == MAGIC;
}

void LightPersistenceDriver::load(bool &lightOn, uint16_t &hoursElapsed)
{
    uint8_t stateRaw;
    EEPROM.get(BASE_ADDR + 1, stateRaw);
    EEPROM.get(BASE_ADDR + 2, hoursElapsed);
    lightOn = (stateRaw == 1);
}

void LightPersistenceDriver::save(bool lightOn, uint16_t hoursElapsed)
{
    // Invalida o magic primeiro para evitar dados corrompidos
    // em caso de queda de energia durante a escrita
    EEPROM.update(BASE_ADDR, 0);
    EEPROM.update(BASE_ADDR + 1, lightOn ? 1 : 0);
    EEPROM.put(BASE_ADDR + 2, hoursElapsed);  // put usa update internamente
    EEPROM.update(BASE_ADDR, MAGIC);           // valida por último
}

void LightPersistenceDriver::reset()
{
    EEPROM.update(BASE_ADDR, 0);  // invalida magic; próximo boot inicia do zero
}
