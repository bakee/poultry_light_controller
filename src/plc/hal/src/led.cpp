#include "../inc/led.h"

namespace hal
{
    Led* Led::_instance = NULL;
    
    //************************************
    // Method:    Led
    // FullName:  hal::Led::Led
    // Access:    private
    // Returns:
    // Qualifier:
    //************************************
    Led::Led()
    {
        _heartBeatPin.DDR = &DDRG;
        _heartBeatPin.PORT = &PORTG;
        _heartBeatPin.PinNo = 0;
        
        SET_MC_PIN_OUTPUT(_heartBeatPin);
        _isHeartBeatLedTurnedOn = false;
        
    }
    
    //************************************
    // Method:    GetInstance
    // FullName:  hal::Led::GetInstance
    // Access:    public static
    // Returns:   Led*
    // Qualifier:
    //************************************
    Led* Led::GetInstance()
    {
        if (_instance == NULL)
        {
            static Led object;
            _instance = &object;
        }
        
        return _instance;
    }
    
    //************************************
    // Method:    ToggleHearBeatLed
    // FullName:  hal::Led::ToggleHearBeatLed
    // Access:    public
    // Returns:   void
    // Qualifier:
    //************************************
    void Led::ToggleHearBeatLed()
    {
        if(!_isHeartBeatLedTurnedOn)
        {
            SET_MC_PIN_HIGH(_heartBeatPin);
        }
        else
        {
            SET_MC_PIN_LOW(_heartBeatPin);
        }
        
        _isHeartBeatLedTurnedOn = !_isHeartBeatLedTurnedOn;
    }
};
