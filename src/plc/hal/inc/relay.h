#ifndef RELAY_H
#define RELAY_H

#include "hal_utils.h"

namespace hal
{
    typedef struct
    {
        MC_PIN TemperatureRelay1;
        MC_PIN TemperatureRelay2;
    } RELAY_PIN;

    class Relay
    {
        private:
        
        static Relay* _instance;
        
        static const unsigned char NumberOfRelays = 2;
        
        MC_PIN _relays[NumberOfRelays];
        
        Relay( void );
        
        void TurnOnOrOff(unsigned char relayNumber, bool onOrOff);

        public:
        
        static Relay* GetInstance( void );
        
        void TurnOn( unsigned char relayNumber );
        
        void TurnOff( unsigned char relayNumber );
        
        bool GetState( unsigned char relayNumber );
    };
};

#endif