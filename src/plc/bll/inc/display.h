/*
* display.g
*
* Created: 1/19/2013 6:52:29 PM
*  Author: muhammad
*/


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "../../hal/inc/seven_segment.h"

namespace bll
{
    class DisplayName
    {
        public:
        typedef enum
        {
            Temperature,
            Humidity,
            Timer
        } EDisplayName;
    };
    
    class Display
    {
        private:
        
        static Display* _instance;
        
        hal::SevenSegment* _sevenSegment;
        
        //************************************
        // Method:    Display
        // FullName:  bll::Display::Display
        // Access:    private
        // Returns:
        // Qualifier:
        // Parameter: void
        //************************************
        Display( void );
        
        public:
        
        //************************************
        // Method:    GetInstance
        // FullName:  bll::Display::GetInstance
        // Access:    public static
        // Returns:   Display*
        // Qualifier:
        // Parameter: void
        //************************************
        static Display* GetInstance( void );
        
        //************************************
        // Method:    Show
        // FullName:  bll::Display::Show
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned int value
        // Parameter: DisplayName::EDisplayName displayName
        //************************************
        void Show( unsigned int value, DisplayName::EDisplayName displayName );
    };
};


#endif /* DISPLAY_H_ */