#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

#include "../../hal/inc/relay.h"
#include "../inc/task_dispatcher.h"
#include "../inc/relay_settings.h"
#include "../inc/system_time.h"

namespace bll
{
    class RelayName
    {
        public:
        typedef enum
        {
            LightControllerRelay
        } ERelayName;
    };
    
    class SetupState
    {
        public:
        typedef enum
        {
            FirstTimeOn,
            FirstTimeOff,
            SecondTimeOn,
            SecondTimeOff
        } ESetupState;
    };
    
    void FriendDecrementTimout( void );
    
    class RelayManager
    {
        private:
        
        static RelayManager* _instance;
        
        hal::Relay* _relay;
               
        RelaySettings* _relaySettings;
        
        SystemTime* _systemTime;

        volatile bool _isApplicationRunning;
        
        unsigned int _temperatureRelay2TimerValue;

        bool _isTemperatureRelay2TimerEnabled;
        
        unsigned int _temperatureRelay3TimerValue;
        bool _isTemperatureRelay3TimerEnabled;
        
        unsigned int _timer1TimeoutValue;
        
        unsigned int _timer2TimeoutValue;
        
        unsigned int _timer2TurnOnTimeoutValue;
        
        RelayManager( void );
        
        void DecrementTimeout( void );        
        
        public:
        
        static RelayManager* GetInstance( void );
        
        void TurnOn( RelayName::ERelayName relayName );
        
        void TurnOff( RelayName::ERelayName relayName );
        
        bool GetRelayState( RelayName::ERelayName relayName );
        
        bool GetApplicationState( void );
        
        void StartManagingRelays( void );
        
        void ManageRelays( void );
        
        void SetRelaySettings( RelaySettings* relaySettings );       
        
        unsigned int GetTimer2RemainingTime( void );
        
        friend void FriendDecrementTimout( void );
    };
};

#endif
