// ==========================================================
// File: include/drivers/LightPersistenceDriver.h
// ==========================================================
//
// Layout EEPROM (4 bytes a partir do endereço 0):
//   Addr 0 : magic byte (0xBE = dados válidos)
//   Addr 1 : estado da luz (1 = ON, 0 = OFF)
//   Addr 2-3 : horas decorridas na fase atual (uint16_t)
//
// O magic é escrito POR ÚLTIMO para garantir que dados
// parciais causados por queda de energia sejam ignorados.
// ==========================================================

#ifndef LIGHT_PERSISTENCE_DRIVER_H
#define LIGHT_PERSISTENCE_DRIVER_H

#include <Arduino.h>

class LightPersistenceDriver
{
private:
    static const int BASE_ADDR = 0;
    static const uint8_t MAGIC = 0xBE;

public:
    void begin();

    bool hasValidData();

    void load(bool &lightOn, uint16_t &hoursElapsed);
    void save(bool lightOn, uint16_t hoursElapsed);

    void reset();
};

#endif
