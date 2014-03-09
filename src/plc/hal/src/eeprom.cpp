/*
* eeprom.cpp
*
* Created: 1/13/2013 8:34:02 PM
*  Author: muhammad
*/

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
    
    //************************************
    // Method:    Eeprom
    // FullName:  hal::Eeprom::Eeprom
    // Access:    private
    // Returns:
    // Qualifier:
    //************************************
    Eeprom::Eeprom()
    {
        _eepromReadyCallback = NULL;
    }
    
    //************************************
    // Method:    GetInstance
    // FullName:  hal::Eeprom::GetInstance
    // Access:    public static
    // Returns:   Eeprom*
    // Qualifier:
    //************************************
    Eeprom* Eeprom::GetInstance()
    {
        if(_instance == NULL)
        {
            static Eeprom object;
            _instance = &object;
        }
        
        return _instance;
    }
    
    //************************************
    // Method:    Read
    // FullName:  hal::Eeprom::Read
    // Access:    public
    // Returns:   unsigned char
    // Qualifier:
    // Parameter: unsigned int address
    //************************************
    unsigned char Eeprom::Read( unsigned int address )
    {
        while( EECR & ( 1 << EEWE )); // For safety
        
        EEAR = address;
        EECR |= ( 1 << EERE );
        
        return EEDR;
    }
    
    //************************************
    // Method:    Write
    // FullName:  hal::Eeprom::Write
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: unsigned int address
    // Parameter: unsigned char data
    //************************************
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
    
    //************************************
    // Method:    IsEepromReady
    // FullName:  hal::Eeprom::IsEepromReady
    // Access:    public
    // Returns:   bool
    // Qualifier:
    //************************************
    bool Eeprom::IsEepromReady()
    {
        return !(EECR & ( 1 << EEWE ));
    }

    //************************************
    // Method:    Vector22
    // FullName:  hal::Eeprom::Vector22
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
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

    //************************************
    // Method:    __vector_22
    // FullName:  hal::__vector_22
    // Access:    public
    // Returns:   void
    // Qualifier:
    //************************************
    void __vector_22()
    {
        Eeprom::_instance->Vector22();
    }
};