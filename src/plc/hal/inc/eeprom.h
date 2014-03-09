/*
* eeprom.h
*
* Created: 1/13/2013 8:33:50 PM
*  Author: muhammad
*/


#ifndef EEPROM_H_
#define EEPROM_H_

#include "hal_utils.h"

namespace hal
{
    typedef void (*EepromReadyCallback)( void );
    
    class Eeprom
    {
        private:
        
        static Eeprom* _instance;
        
        EepromReadyCallback _eepromReadyCallback;
        
        //************************************
        // Method:    Eeprom
        // FullName:  hal::Eeprom::Eeprom
        // Access:    private
        // Returns:
        // Qualifier:
        // Parameter: void
        //************************************
        Eeprom( void );
        
        //************************************
        // Method:    Vector22
        // FullName:  hal::Eeprom::Vector22
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Vector22( void );
        
        public:
        
        //************************************
        // Method:    GetInstance
        // FullName:  hal::Eeprom::GetInstance
        // Access:    public static
        // Returns:   Eeprom*
        // Qualifier:
        // Parameter: void
        //************************************
        static Eeprom* GetInstance( void );
        
        //************************************
        // Method:    Read
        // FullName:  hal::Eeprom::Read
        // Access:    public
        // Returns:   unsigned char
        // Qualifier:
        // Parameter: unsigned int address
        //************************************
        unsigned char Read( unsigned int address );
        
        //************************************
        // Method:    Write
        // FullName:  hal::Eeprom::Write
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned int address
        // Parameter: unsigned char data
        //************************************
        void Write( unsigned int address, unsigned char data );
        
        //************************************
        // Method:    IsEepromReady
        // FullName:  hal::Eeprom::IsEepromReady
        // Access:    public
        // Returns:   bool
        // Qualifier:
        // Parameter: void
        //************************************
        bool IsEepromReady( void );
        
        //************************************
        // Method:    EepromReadyCallback
        // FullName:  hal::EepromReadyCallback
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: EepromReadyCallback callback
        //************************************
        void SetEepromReadyCallback( EepromReadyCallback callback );
        
        //************************************
        // Method:    __vector_22
        // FullName:  hal::__vector_22
        // Access:    public
        // Returns:   friend void
        // Qualifier:
        // Parameter: void
        //************************************
        friend void __vector_22( void );
    };
};

#endif /* EEPROM_H_ */