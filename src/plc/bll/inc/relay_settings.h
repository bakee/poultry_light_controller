#ifndef RELAY_SETTINGS_H_
#define RELAY_SETTINGS_H_

#include "relay_time.h"

#define NUMBER_OF_SETTINGS 4
typedef struct
{
    RelayTime relayTimes[NUMBER_OF_SETTINGS];
} RelaySettings;

#endif
