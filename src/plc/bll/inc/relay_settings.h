#ifndef RELAY_SETTINGS_H_
#define RELAY_SETTINGS_H_

typedef struct
{
    unsigned int defaultTemperature;

    unsigned int defaultHumidity;

    unsigned int defaultOxygenLevel;
    
    unsigned int temperatureRelay2Interval;

    unsigned int temperatureRelay3Interval;
    
    unsigned int timer1RelayInterval;

    unsigned int timer2RelayInterval;

    unsigned int timer2TurnOntime;
    
} RelaySettings;

#endif