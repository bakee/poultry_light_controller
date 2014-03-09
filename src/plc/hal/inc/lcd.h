#ifndef LCD_H
#define LCD_H

#include "hal_utils.h"

namespace hal
{
    typedef struct
    {
        MC_PIN LCD_E;
        MC_PIN LCD_RS;
        MC_PIN DATA_4;
        MC_PIN DATA_5;
        MC_PIN DATA_6;
        MC_PIN DATA_7;
    } LCD_PINS;

    class Lcd
    {
        private:
        
        static Lcd* _instance;
        
        MC_PIN _lcdPins[6]; // DATA4, DATA5, DATA6, DATA7, LCD_RS and LCD_E

        Lcd( void );

        void Initialize( void );
        
        void SetTo4BitMode( void );
        
        void InitializePort();
        
        void SetTo8BitMode( void );
        
        void Send(unsigned char c, unsigned char cc);
        
        void Write(unsigned char);
        
        void SendCommand(unsigned char);
        
        void SetData(unsigned char nibble);

        void ResetE( void );
        
        void SetE( void );

        public:
        
        static Lcd* GetInstance( void );

        void SendString(const char *data, bool shouldFillUpWithSpace = true);
        
        void Clear( void );
        
        void ClearLine(unsigned char lineNumber);
        
        void Goto(unsigned char x, unsigned char y);
        
        void SendNumber(unsigned int number);
        
        void SendSingleCharacter(char character);
        
        void DefineCustomCharacter(unsigned char index, unsigned char* data, unsigned char numberOfCharacter = 1);
        
        void Refresh( void );
    };
};

#endif