#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

#include "../../hal/inc/relay.h"
#include "../inc/task_dispatcher.h"
#include "../inc/relay_settings.h"
#include "../inc/sensor.h"

namespace bll
{
    class RelayName
    {
        public:
        typedef enum
        {
            TemperatureRelay1,
            TemperatureRelay2,
            TemperatureRelay3,
            TemperatureRelay4,
            HumidityRelay,
            Timer1Relay,
            Timer2Relay,
            OxygenRelay
        } ERelayName;
    };
    
    class SetupState
    {
        public:
        typedef enum
        {
            DefaultTemperature,
            TemperatureRelay2Interval,
            TemperatureRelay3Interval,
            DefaultHumidity,
            Timer1RelayInterval,
            Timer2RelayInterval,
            Timer2TurnOntime,
            DefaultOxygenLevel
        } ESetupState;
    };
    
    void FriendDecrementTimout( void );
    
    class RelayManager
    {
        private:
        
        static RelayManager* _instance;
        
        hal::Relay* _relay;
        
        Sensor* _sensor;
        
        RelaySettings* _relaySettings;
        
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
        
        TemperatureRelaySettings _temperatureRelay1Settings;
        
        TemperatureRelaySettings _temperatureRelay2Settings;
        
        TemperatureRelaySettings _temperatureRelay3Settings;
        
        TemperatureRelaySettings _temperatureRelay4Settings;
        
        public:
        
        static RelayManager* GetInstance( void );
        
        void TurnOn( RelayName::ERelayName relayName );
        
        void TurnOff( RelayName::ERelayName relayName );
        
        bool GetRelayState( RelayName::ERelayName relayName );
        
        bool GetApplicationState( void );
        
        void StartManagingRelays( void );
        
        void ManageRelays( void );
        
        void SetRelaySettings( RelaySettings* relaySettings );
        
        void UpdateTimeoutValues( void );
        
        unsigned int GetTimer2RemainingTime( void );
        
        friend void FriendDecrementTimout( void );
    };
};

#endif // RELAY_MANAGER_H
