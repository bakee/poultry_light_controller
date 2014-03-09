/*
* display.cpp
*
* Created: 1/19/2013 6:53:00 PM
*  Author: muhammad
*/

#include "../inc/display.h"
#include "../inc/relay_manager.h"

namespace bll
{
    using namespace hal;
    
    Display* Display::_instance = NULL;
    
    //************************************
    // Method:    Display
    // FullName:  bll::Display::Display
    // Access:    private
    // Returns:
    // Qualifier:
    // Parameter: void
    //************************************
    Display::Display( void )
    {
        _sevenSegment = SevenSegment::GetInstance();
    }

    //************************************
    // Method:    GetInstance
    // FullName:  bll::Display::GetInstance
    // Access:    public static
    // Returns:   Display*
    // Qualifier:
    // Parameter: void
    //************************************
    Display* Display::GetInstance( void )
    {
        if (_instance == NULL)
        {
            static Display object;
            _instance = &object;
        }
        
        return _instance;
    }

    //************************************
    // Method:    Show
    // FullName:  bll::Display::Show
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: unsigned int value
    // Parameter: DisplayName::EDisplayName displayName
    //************************************
    void Display::Show( unsigned int value, DisplayName::EDisplayName displayName )
    {
        if(RelayManager::GetInstance()->GetApplicationState() == false)
        {
            _sevenSegment->SetDisplayMode(DisplayMode::Dashed);
            return;
        }
        
        _sevenSegment->SetDisplayMode(DisplayMode::Normal);
        
        if(value > 9999)
        {
            return;
        }
        
        unsigned char values[4];
        
        for (unsigned char i = 0; i < 4; ++i)
        {
            values[i] = 0;
        }
        
        unsigned char index = 0;
        while(value > 0)
        {
            values[index] = value % 10;
            value = value / 10;
            index++;
        }
        
        switch (displayName)
        {
            case DisplayName::Temperature:
            _sevenSegment->SetDisplayValue(0, values[3]);
            _sevenSegment->SetDisplayValue(1, values[2]);
            _sevenSegment->SetDisplayValue(2, values[1] | 0x80); // Need to show decimal point with this one
            _sevenSegment->SetDisplayValue(3, values[0]);
            break;
            
            case DisplayName::Humidity:
            _sevenSegment->SetDisplayValue(4, values[3]);
            _sevenSegment->SetDisplayValue(5, values[2]);
            _sevenSegment->SetDisplayValue(6, values[1] | 0x80); // Need to show decimal point with this one
            _sevenSegment->SetDisplayValue(7, values[0]);
            break;
            
            case DisplayName::Timer:
            _sevenSegment->SetDisplayValue(8, values[2] | 0x80); // Need to show decimal point with this one
            _sevenSegment->SetDisplayValue(9, values[1]);
            _sevenSegment->SetDisplayValue(10, values[0]);
            break;
        }
    }

};