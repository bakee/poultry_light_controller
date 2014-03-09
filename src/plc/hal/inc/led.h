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
        
        Led( void );
        
        public:
        
        static Led* GetInstance( void );
        
        void ToggleHearBeatLed( void );
    };
};

#endif // LED_H
