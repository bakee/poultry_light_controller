/*
* ds18b20.cpp
*
* Created: 1/28/2013 1:41:58 AM
*  Author: muhammad
*/

#include "../inc/ds18b20.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


// For better performance new definitions are used for this file only, 
// since this is a very time critical device
#define DS18B20_PORT PORTF
#define DS18B20_DDR DDRF
#define DS18B20_PIN PINF
#define DS18B20_PIN_NO 0

#ifdef SET_MC_PIN_HIGH
#undef SET_MC_PIN_HIGH
#endif
#define SET_MC_PIN_HIGH(x) (DS18B20_PORT |= 1 << DS18B20_PIN_NO)

#ifdef SET_MC_PIN_LOW
#undef SET_MC_PIN_LOW
#endif
#define SET_MC_PIN_LOW(x) (DS18B20_PORT &= ~(1 << DS18B20_PIN_NO))

#ifdef SET_MC_PIN_OUTPUT
#undef SET_MC_PIN_OUTPUT
#endif
#define SET_MC_PIN_OUTPUT(x) (DS18B20_DDR |= 1 << DS18B20_PIN_NO)


#ifdef SET_MC_PIN_INPUT
#undef SET_MC_PIN_INPUT
#endif
#define SET_MC_PIN_INPUT(x) (DS18B20_DDR &= ~(1 << DS18B20_PIN_NO))


#ifdef IS_MC_PIN_LOW
#undef IS_MC_PIN_LOW
#endif
#define IS_MC_PIN_LOW(x) (((DS18B20_PIN >> DS18B20_PIN_NO) & 0x01) == 0x00)

#ifdef IS_MC_PIN_HIGH
#undef IS_MC_PIN_HIGH
#endif
#define IS_MC_PIN_HIGH(x) (((DS18B20_PIN >> DS18B20_PIN_NO) & 0x01) == 0x01)

namespace hal
{
    
    Ds18b20* Ds18b20::_instance = NULL;

    Ds18b20::Ds18b20( void )
    {
        _pin.DDR = &DDRF;
        _pin.PORT = &PORTF;
        _pin.PIN = &PINF;
        _pin.PinNo = 0;
    }

    Ds18b20* Ds18b20::GetInstance( void )
    {
        if(_instance == NULL)
        {
            static Ds18b20 object;
            _instance = & object;
        }
        
        return _instance;
    }

    bool Ds18b20::SendResetPulse()
    {
        SET_MC_PIN_LOW(_pin);
        SET_MC_PIN_OUTPUT(_pin);
        _delay_us(480);
        
        // Get presense pulse
        SET_MC_PIN_INPUT(_pin);
        
        cli();
        _delay_us(60);
        
        if(IS_MC_PIN_LOW(_pin))
        {
            sei();
            _delay_us(420);
            return true;
        }
        
        sei();
        _delay_us(420);
        return false;
    }

    bool Ds18b20::ReadBit( void )
    {
        SET_MC_PIN_LOW(_pin);
        cli();
        SET_MC_PIN_OUTPUT(_pin);
        _delay_us(1);
        
        SET_MC_PIN_INPUT(_pin);
        _delay_us(2);
        bool isDataLineHigh = IS_MC_PIN_HIGH(_pin);
        sei();
        
        _delay_us(57);

        return isDataLineHigh;
    }

    void Ds18b20::WriteBit( bool dataBit)
    {
        SET_MC_PIN_LOW(_pin);
        cli();
        SET_MC_PIN_OUTPUT(_pin);
        _delay_us(1);
        
        if(dataBit)
        {
            SET_MC_PIN_HIGH(_pin);
        }
        _delay_us(59);
        sei();
        SET_MC_PIN_INPUT(_pin);
    }

    unsigned char Ds18b20::ReadByte( void )
    {
        unsigned char data = 0;
        
        for (int i = 0; i < 8; ++i)
        {
            data |= (ReadBit() << i);
        }
        
        return data;
    }

    void Ds18b20::WriteByte( unsigned char dataByte )
    {
        for (int i = 0; i < 8; ++i)
        {
            WriteBit(dataByte & (1 << i));
        }
    }

    void Ds18b20::StartConversion( void )
    {
        if(SendResetPulse())
        {
            WriteByte(Command::SkipRom);
            WriteByte(Command::ConvertT);
        }
    }

    bool Ds18b20::IsConversionCompleted( void )
    {
        return ReadBit();
    }

    unsigned int Ds18b20::GetTemperatureValue( void )
    {
        if(SendResetPulse())
        {
            WriteByte(Command::SkipRom);
            WriteByte(Command::ReadScratchPad);
            
            
            // Read only the first two bytes and ignore rest
            unsigned char tempLow = ReadByte();
            unsigned char tempHigh = ReadByte();
            
            unsigned int finalTemperature = (tempHigh << 8) | tempLow;
            
            finalTemperature = (finalTemperature * 10) / 16;
            
            // Check for error case, assuming the temperature value will not exceed 125.0C.
            if(finalTemperature > 1250)
            {
                return 0;
            }
            return finalTemperature;
        }
        
        return 0;
    }

};