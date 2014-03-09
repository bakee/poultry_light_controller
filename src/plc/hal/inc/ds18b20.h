/*
* ds18b20.h
*
* Created: 1/28/2013 1:40:05 AM
*  Author: muhammad
*/


#ifndef DS18B20_H_
#define DS18B20_H_

#include "hal_utils.h"

namespace hal
{
    class Command
    {
        public:
        typedef enum
        {
            SearchRom = 0xF0,
            ReadRom = 0x33,
            MatchRom = 0x55,
            
            // To skip the sending ROM Code, useful for single unit over the bus operation
            SkipRom = 0xCC,
            AlarmSearch = 0xEC,
            
            // To start conversion, conversion time is 93.75 ms(9 bit), 187.5 ms(10 bit), 375 ms(11 bit), 750 ms(12 bit)
            ConvertT = 0x44,
            
            // To read the data all 9 byte will be sent sequentially LSB first, 0 byte first, but they can be ignored any time by sending a reset pulse
            ReadScratchPad = 0xBE,
            WriteScratchPad = 0x4E,
            CopyScratchPad = 0x48,
            RecallEeprom = 0xB8,
            ReadPowerSupply = 0xB4,
        } ECommand;
    };
    
    class Ds18b20
    {
        private:
        
        static Ds18b20* _instance;
        MC_PIN _pin;
        
        Ds18b20( void );
        
        bool SendResetPulse( void );
        
        bool ReadBit( void );
        void WriteBit( bool dataBit);
        
        unsigned char ReadByte( void );
        void WriteByte( unsigned char dataByte );
        
        public:
        
        static Ds18b20* GetInstance( void );
        
        void StartConversion( void );
        bool IsConversionCompleted( void );
        unsigned int GetTemperatureValue( void );
    };
};

#endif /* DS18B20_H_ */