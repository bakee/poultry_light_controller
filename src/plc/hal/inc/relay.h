#ifndef RELAY_H
#define RELAY_H

#include "hal_utils.h"

namespace hal
{
    typedef struct
    {
        MC_PIN TemperatureRelay1;
        MC_PIN TemperatureRelay2;
        MC_PIN TemperatureRelay3;
        MC_PIN TemperatureRelay4;
        MC_PIN HumidityRelay;
        MC_PIN Timer1Relay;
        MC_PIN Timer2Relay;
        MC_PIN OxygenRelay;
    } RELAY_PIN;

    class Relay
    {
        private:
        
        static Relay* _instance;
        
        static const unsigned char NumberOfRelays = 8;
        
        MC_PIN _relays[NumberOfRelays];
        
        //************************************
        // Method:    Relay
        // FullName:  hal::Relay::Relay
        // Access:    private
        // Returns:
        // Qualifier:
        // Parameter: void
        //************************************
        Relay( void );
        
        //************************************
        // Method:    TurnOnOrOff
        // FullName:  hal::Relay::TurnOnOrOff
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char relayNumber
        // Parameter: bool onOrOff
        //************************************
        void TurnOnOrOff(unsigned char relayNumber, bool onOrOff);

        public:
        
        //************************************
        // Method:    GetInstance
        // FullName:  hal::Relay::GetInstance
        // Access:    public static
        // Returns:   Relay*
        // Qualifier:
        // Parameter: void
        //************************************
        static Relay* GetInstance( void );
        
        //************************************
        // Method:    TurnOn
        // FullName:  hal::Relay::TurnOn
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char relayNumber
        //************************************
        void TurnOn( unsigned char relayNumber );
        
        //************************************
        // Method:    TurnOff
        // FullName:  hal::Relay::TurnOff
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char relayNumber
        //************************************
        void TurnOff( unsigned char relayNumber );
        
        //************************************
        // Method:    GetState
        // FullName:  hal::Relay::GetState
        // Access:    public
        // Returns:   bool
        // Qualifier:
        // Parameter: unsigned char relayNumber
        //************************************
        bool GetState( unsigned char relayNumber );
    };
};

#endif // RELAY_H
