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
        
        Eeprom( void );
        
        void Vector22( void );
        
        public:
        
        static Eeprom* GetInstance( void );
        
        unsigned char Read( unsigned int address );
        
        void Write( unsigned int address, unsigned char data );
        
        bool IsEepromReady( void );
        
        void SetEepromReadyCallback( EepromReadyCallback callback );
        
        friend void __vector_22( void );
    };
};

#endif