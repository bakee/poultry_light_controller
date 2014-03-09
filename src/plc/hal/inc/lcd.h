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

        //************************************
        // Method:    Lcd
        // FullName:  hal::Lcd::Lcd
        // Access:    private
        // Returns:
        // Qualifier:
        // Parameter: void
        //************************************
        Lcd( void );

        //************************************
        // Method:    Initialize
        // FullName:  hal::Lcd::Initialize
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Initialize( void );
        
        //************************************
        // Method:    SetTo4BitMode
        // FullName:  hal::Lcd::SetTo4BitMode
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void SetTo4BitMode( void );
        
        //************************************
        // Method:    InitializePort
        // FullName:  hal::Lcd::InitializePort
        // Access:    private
        // Returns:   void
        // Qualifier:
        //************************************
        void InitializePort();
        
        //************************************
        // Method:    SetTo8BitMode
        // FullName:  hal::Lcd::SetTo8BitMode
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void SetTo8BitMode( void );
        
        //************************************
        // Method:    Send
        // FullName:  hal::Lcd::Send
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char c
        // Parameter: unsigned char cc
        //************************************
        void Send(unsigned char c, unsigned char cc);
        
        //************************************
        // Method:    Write
        // FullName:  hal::Lcd::Write
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char
        //************************************
        void Write(unsigned char);
        
        //************************************
        // Method:    SendCommand
        // FullName:  hal::Lcd::SendCommand
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char
        //************************************
        void SendCommand(unsigned char);
        
        //************************************
        // Method:    SetData
        // FullName:  hal::Lcd::SetData
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char nibble
        //************************************
        void SetData(unsigned char nibble);
        
        //************************************
        // Method:    ResetE
        // FullName:  hal::Lcd::ResetE
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void ResetE( void );
        
        //************************************
        // Method:    SetE
        // FullName:  hal::Lcd::SetE
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void SetE( void );

        public:
        
        //************************************
        // Method:    GetInstance
        // FullName:  hal::Lcd::GetInstance
        // Access:    public static
        // Returns:   Lcd*
        // Qualifier:
        // Parameter: void
        //************************************
        static Lcd* GetInstance( void );
        
        //************************************
        // Method:    SendString
        // FullName:  hal::Lcd::SendString
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: const char * data
        // Parameter: bool shouldFillUpWithSpace
        //************************************
        void SendString(const char *data, bool shouldFillUpWithSpace = true);
        
        //************************************
        // Method:    Clear
        // FullName:  hal::Lcd::Clear
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Clear( void );
        
        //************************************
        // Method:    ClearLine
        // FullName:  hal::Lcd::ClearLine
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char lineNumber
        //************************************
        void ClearLine(unsigned char lineNumber);
        
        //************************************
        // Method:    Goto
        // FullName:  hal::Lcd::Goto
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char x
        // Parameter: unsigned char y
        //************************************
        void Goto(unsigned char x, unsigned char y);
        
        //************************************
        // Method:    SendNumber
        // FullName:  hal::Lcd::SendNumber
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned int number
        //************************************
        void SendNumber(unsigned int number);
        
        //************************************
        // Method:    SendSingleCharacter
        // FullName:  hal::Lcd::SendSingleCharacter
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: char character
        //************************************
        void SendSingleCharacter(char character);
        
        void DefineCustomCharacter(unsigned char index, unsigned char* data, unsigned char numberOfCharacter = 1);
        
        void Refresh( void );
    };
};

#endif // LCD_H
