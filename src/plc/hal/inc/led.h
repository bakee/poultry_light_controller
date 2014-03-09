#ifndef LED_H
#define LED_H

#include "hal_utils.h"

namespace hal
{
    class Led
    {
        private:
        
        static Led* _instance;
        
        bool _isHeartBeatLedTurnedOn;
        
        MC_PIN _heartBeatPin;
        
        //************************************
        // Method:    Led
        // FullName:  hal::Led::Led
        // Access:    private
        // Returns:
        // Qualifier:
        // Parameter: void
        //************************************
        Led( void );
        
        public:
        
        //************************************
        // Method:    GetInstance
        // FullName:  hal::Led::GetInstance
        // Access:    public static
        // Returns:   Led*
        // Qualifier:
        // Parameter: void
        //************************************
        static Led* GetInstance( void );
        
        //************************************
        // Method:    ToggleHearBeatLed
        // FullName:  hal::Led::ToggleHearBeatLed
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void ToggleHearBeatLed( void );
    };
};

#endif // LED_H
