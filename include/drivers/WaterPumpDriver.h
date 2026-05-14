// ======================================
// File: include/drivers/WaterPumpDriver.h
// ======================================

#ifndef WATER_PUMP_DRIVER_H
#define WATER_PUMP_DRIVER_H

#include <Arduino.h>

class WaterPumpDriver
{
private:
    int controlPin;

    bool running;
    unsigned long startTime;

    const unsigned long RUN_TIME = 5000; // 5 segundos

public:
    WaterPumpDriver(int pin);

    void begin();

    void start();
    
    void stop();

    void update();

    bool isRunning();
};

#endif