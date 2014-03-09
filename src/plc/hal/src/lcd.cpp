#include <avr/io.h>
#include <util/delay.h>
#include "../inc/lcd.h"

namespace hal
{
    Lcd* Lcd::_instance = NULL;
    
    Lcd::Lcd()
    {
        Initialize();
    }
    
    Lcd* Lcd::GetInstance()
    {
        if (_instance == NULL)
        {
            static Lcd object;
            _instance = &object;
        }
        
        return _instance;
    }

    void Lcd::SendString(const char *data, bool shouldFillUpWithSpace)
    {
        unsigned char i;
        char j;
        for (i = 0;(j = data[i]); ++i)
        {
            SendSingleCharacter(j);
        }
        
        if (shouldFillUpWithSpace)
        {
            for (; i < 20; ++i)
            {
                SendSingleCharacter(0x20);
            }
        }
    }

    void Lcd::SetTo8BitMode()
    {
        Write((0x30 >> 4) & 0x0F);
    }

    void Lcd::Write(unsigned char data)
    {
        SetData(data);
        SetE();
        _delay_us(500 + 200);
        ResetE();
        _delay_us(200 + 200);
        SetData(0);
    }

    void Lcd::SetData(unsigned char nibble)
    {
        for (unsigned char i = 0; i < 5; ++i)
        {
            if(nibble & (1 << i))
            {
                SET_MC_PIN_HIGH(_lcdPins[i]);
            }
            else
            {
                SET_MC_PIN_LOW(_lcdPins[i]);
            }
        }
    }

    void Lcd::SetE()
    {
        SET_MC_PIN_HIGH(_lcdPins[5]);
    }

    void Lcd::ResetE()
    {
        SET_MC_PIN_LOW(_lcdPins[5]);
    }

    void Lcd::Send(unsigned char data, unsigned char commandOrData)
    {
        Write(((data >> 4) & 0x0F) | (commandOrData << 4)); // Higher nibble
        Write((data & 0x0F) | (commandOrData << 4)); // Lower nibble
    }

    void Lcd::SendSingleCharacter(char data)
    {
        Send(data, 1);
    }

    void Lcd::SendCommand(unsigned char command)
    {
        Send(command, 0);
    }

    void Lcd::Initialize()
    {
        Lcd::InitializePort();
        Lcd::SetTo4BitMode();
    }

    void Lcd::InitializePort()
    {
        LCD_PINS pins;

        pins.DATA_4.DDR = &DDRB;
        pins.DATA_4.PORT = &PORTB;
        pins.DATA_4.PinNo = 4;

        pins.DATA_5.DDR = &DDRB;
        pins.DATA_5.PORT = &PORTB;
        pins.DATA_5.PinNo = 5;

        pins.DATA_6.DDR = &DDRB;
        pins.DATA_6.PORT = &PORTB;
        pins.DATA_6.PinNo = 6;

        pins.DATA_7.DDR = &DDRB;
        pins.DATA_7.PORT = &PORTB;
        pins.DATA_7.PinNo = 7;

        pins.LCD_RS.DDR = &DDRB;
        pins.LCD_RS.PORT = &PORTB;
        pins.LCD_RS.PinNo = 2;

        pins.LCD_E.DDR = &DDRB;
        pins.LCD_E.PORT = &PORTB;
        pins.LCD_E.PinNo = 3;

        _lcdPins[0] = pins.DATA_4;
        _lcdPins[1] = pins.DATA_5;
        _lcdPins[2] = pins.DATA_6;
        _lcdPins[3] = pins.DATA_7;
        _lcdPins[4] = pins.LCD_RS;
        _lcdPins[5] = pins.LCD_E;

        // DDR Initialization
        for (unsigned int i = 0; i < 6; ++i)
        {
            SET_MC_PIN_OUTPUT(_lcdPins[i]);
        }
    }

    void Lcd::SetTo4BitMode()
    {
        _delay_ms(50);
        SetTo8BitMode();
        SetTo8BitMode();
        SetTo8BitMode();
        Write((0x20 >> 4) & 0x0F);
        _delay_ms(10);
        SendCommand(0x28);
        SendCommand(0x0C);
    }

    void Lcd::Goto(unsigned char x, unsigned char y)
    {
        switch (y)
        {
            case 0:
            SendCommand(0x80 + x);
            break;
            case 1:
            SendCommand(0xC0 + x);
            break;
            case 2:
            SendCommand(0x80 + 20 + x);
            break;
            case 3:
            SendCommand(0xC0 + 20 + x);
            break;
            default:
            break;
        }
    }

    void Lcd::Clear()
    {
        SendCommand(0x01);
        _delay_ms(1);
    }
    
    void Lcd::ClearLine(unsigned char lineNumber)
    {
        Goto(0, lineNumber);
        SendString("");
    }

    void Lcd::SendNumber(unsigned int number)
    {
        if (0 == number)
        SendSingleCharacter(48);
        else
        {
            int i = 0;
            unsigned char j[5];
            unsigned int k = 0;
            for (i = 0; i < 5; ++i)
            {
                j[i] = 0;
            }

            k = number;
            for (i = 0; k > 0; ++i)
            {
                j[i] = k % 10;
                k /= 10;
            }

            k = i - 1;
            for (i = k; i >= 0;--i)
            {
                SendSingleCharacter(j[i] + 48);
            }
        }
    }

    void Lcd::DefineCustomCharacter( unsigned char index, unsigned char* data, unsigned char numberOfCharacter )
    {
        SendCommand(0x40 | index * 8);
        for (unsigned char i = 0; numberOfCharacter * 8 > i; ++i)
        {
            SendSingleCharacter(*(data + i));
        }
    }

    void Lcd::Refresh( void )
    {
        Initialize();
        Clear();
    }

};