#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG_ENABLED ENABLE_DEBUG //flag definida no .ini

#if DEBUG_ENABLED

    #define DEBUG_PRINT(x) Serial.print(x)
    #define DEBUG_PRINTLN(x) Serial.println(x)

#else

    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)

#endif

#endif