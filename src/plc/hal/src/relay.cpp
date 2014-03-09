#include <avr/io.h>
#include "../inc/relay.h"

#define RELAY_MACRO(x, y, m, n) \
_relays[n].DDR = &DDR ## y;\
_relays[n].PORT = &PORT ## y;\
_relays[n].PinNo = m

namespace hal
{
    Relay* Relay::_instance = NULL;
    
    Relay::Relay()
    {
        RELAY_MACRO(_relays, C, 0, 0);
        RELAY_MACRO(_relays, C, 1, 1);
        RELAY_MACRO(_relays, C, 2, 2);
        RELAY_MACRO(_relays, C, 3, 3);
        RELAY_MACRO(_relays, C, 4, 4);
        RELAY_MACRO(_relays, C, 5, 5);
        RELAY_MACRO(_relays, C, 6, 6);
        RELAY_MACRO(_relays, C, 7, 7);

        // DDR Initializations

        for (unsigned int i = 0; i < Relay::NumberOfRelays; ++i)
        {
            SET_MC_PIN_OUTPUT(_relays[i]);
        }
    }
    
    Relay* Relay::GetInstance()
    {
        if (_instance == NULL)
        {
            static Relay object;
            _instance = &object;
        }
        
        return _instance;
    }

    void Relay::TurnOn( unsigned char relayNumber )
    {
        TurnOnOrOff(relayNumber, true);
    }

    void Relay::TurnOff( unsigned char relayNumber )
    {
        TurnOnOrOff(relayNumber, false);
    }

    void Relay::TurnOnOrOff( unsigned char relayNumber, bool onOrOff )
    {
        if (relayNumber >= Relay::NumberOfRelays)
        {
            return;
        }

        if(onOrOff)
        {
            SET_MC_PIN_HIGH(_relays[relayNumber]);
        }
        else
        {
            SET_MC_PIN_LOW(_relays[relayNumber]);
        }
    }

    bool Relay::GetState( unsigned char relayNumber )
    {
        if (relayNumber >= Relay::NumberOfRelays)
        {
            return false;
        }
        
        if ((*(_relays[relayNumber].PORT) & (1 << _relays[relayNumber].PinNo)) == 0)
        {
            return false;
        }
        
        return true;
    }

};