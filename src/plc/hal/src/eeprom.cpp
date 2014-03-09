#include <avr/io.h>
#include <avr/interrupt.h>
#include "../inc/eeprom.h"


// If eeprom needs to be programmed with some predefined data put it here and and a .eep file will be generated with the data in hex format
// and then that can be programmed to EEPROM separately
// Example:
//
 #include <avr/eeprom.h>
 unsigned char EEMEM eepromData[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

namespace hal
{
    Eeprom* Eeprom::_instance = NULL;
    
    Eeprom::Eeprom()
    {
        _eepromReadyCallback = NULL;
    }
    
    Eeprom* Eeprom::GetInstance()
    {
        if(_instance == NULL)
        {
            static Eeprom object;
            _instance = &object;
        }
        
        return _instance;
    }
    
    unsigned char Eeprom::Read( unsigned int address )
    {
        while( EECR & ( 1 << EEWE )); // For safety
        
        EEAR = address;
        EECR |= ( 1 << EERE );
        
        return EEDR;
    }
    
    void Eeprom::Write( unsigned int address, unsigned char data )
    {
        while(EECR & ( 1 << EEWE )); // For safety
        
        EEAR = address;
        EEDR = data;
        
        if( SREG & ( 1 << 7 ))
        {
            cli();
            EECR |= ( 1 << EEMWE );
            EECR |= ( 1 << EEWE );
            sei();
        }
        else
        {
            EECR |= ( 1 << EEMWE );
            EECR |= ( 1 << EEWE );
        }
    }
    
    bool Eeprom::IsEepromReady()
    {
        return !(EECR & ( 1 << EEWE ));
    }

    void Eeprom::Vector22( void )
    {
        if(_eepromReadyCallback != NULL)
        {
            _eepromReadyCallback();
        }
    }

    void Eeprom::SetEepromReadyCallback( EepromReadyCallback callback )
    {
        _eepromReadyCallback = callback;
    }

    void __vector_22()
    {
        Eeprom::_instance->Vector22();
    }
};