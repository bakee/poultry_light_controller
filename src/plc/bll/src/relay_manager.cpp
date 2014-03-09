#include "../inc/relay_manager.h"

namespace bll
{
    using namespace hal;
    RelayManager* RelayManager::_instance = NULL;
    
    RelayManager::RelayManager()
    {
        _relay = Relay::GetInstance();
        
        _isApplicationRunning = false;
        
        _temperatureRelay2TimerValue = 0;
        _isTemperatureRelay2TimerEnabled = false;
        
        _temperatureRelay3TimerValue = 0;
        _isTemperatureRelay3TimerEnabled = false;
        
        TaskDispatcher::GetInstance()->AddTask(FriendDecrementTimout);
    }

    RelayManager* RelayManager::GetInstance()
    {
        if (_instance == NULL)
        {
            static RelayManager object;
            _instance = &object;
        }
        
        return _instance;
    }

    void RelayManager::TurnOn( RelayName::ERelayName relayName )
    {
        _relay->TurnOn(relayName);
    }

    void RelayManager::TurnOff( RelayName::ERelayName relayName )
    {
        _relay->TurnOff(relayName);
    }

    bool RelayManager::GetRelayState( RelayName::ERelayName relayName )
    {
        return _relay->GetState(relayName);
    }
    
    void RelayManager::ManageRelays( void )
    {
        // If application is in configuration mode do not manage relays
        if(!_isApplicationRunning)
        {
            return;
        }
    }
    
    unsigned int RelayManager::GetTimer2RemainingTime( void )
    {
        unsigned int remainingMinute = _timer2TimeoutValue / 60;
        unsigned int remainingHour = remainingMinute / 60;
        remainingMinute = remainingMinute % 60;
        return remainingHour * 100 + remainingMinute;
    }

    void RelayManager::SetRelaySettings( RelaySettings* relaySettings )
    {
        _relaySettings = relaySettings;
        UpdateTimeoutValues();
    }
    
    void RelayManager::UpdateTimeoutValues( void )
    {
        _timer1TimeoutValue = _relaySettings->timer1RelayInterval;
        _timer2TimeoutValue = _relaySettings->timer2RelayInterval * 60; // The settings value is in minute so convert it to seconds
        _timer2TurnOnTimeoutValue = 0;
    }
    
    void FriendDecrementTimout( void )
    {
        RelayManager::GetInstance()->DecrementTimeout();
    }

    void RelayManager::DecrementTimeout( void )
    {
        // If application is in configuration mode do not manage relays
        if(!_isApplicationRunning)
        {
            return;
        }
        
        static unsigned char loop = 0;
        loop++;
        if(loop < TaskDispatcher::GetInterruptRate())
        {
            return;
        }
        else
        {
            loop = 0;
        }
        
        
        // Timer1 Relay Hanling
        if(_timer1TimeoutValue > 0)
        {
            _timer1TimeoutValue--;
            
            if(_timer1TimeoutValue == 0)
            {
                _timer1TimeoutValue = _relaySettings->timer1RelayInterval;
                if(GetRelayState(RelayName::Timer1Relay))
                {
                    TurnOff(RelayName::Timer1Relay);
                }
                else
                {
                    TurnOn(RelayName::Timer1Relay);
                }
            }
        }
        
        
        // Timer2 Relay Handling
        if(_timer2TimeoutValue > 0)
        {
            _timer2TimeoutValue--;
            
            if(_timer2TimeoutValue == 0)
            {
                _timer2TimeoutValue = _relaySettings->timer2RelayInterval * 60;
                _timer2TurnOnTimeoutValue = _relaySettings->timer2TurnOntime + 1; // Since in the next if condition it will be decremented by 1 on this same timeout
                
                TurnOn(RelayName::Timer2Relay);
            }
        }
        
        // Timer2 Turn On Time Handling
        if(_timer2TurnOnTimeoutValue > 0)
        {
            _timer2TurnOnTimeoutValue--;
            
            if(_timer2TurnOnTimeoutValue == 0)
            {
                TurnOff(RelayName::Timer2Relay);
            }
        }
        
        // Temperature Relay 2 Handling
        if(_isTemperatureRelay2TimerEnabled)
        {
            if(_temperatureRelay2TimerValue > 0)
            {
                _temperatureRelay2TimerValue--;
                
                if(_temperatureRelay2TimerValue == 0)
                {
                    TurnOn(RelayName::TemperatureRelay2);
                    _isTemperatureRelay3TimerEnabled = true;
                    _temperatureRelay3TimerValue = _relaySettings->temperatureRelay3Interval;
                }
            }
        }
        
        // Temperature Relay 3 Handling
        if(_isTemperatureRelay3TimerEnabled)
        {
            if(_temperatureRelay3TimerValue > 0)
            {
                _temperatureRelay3TimerValue--;
                
                if(_temperatureRelay3TimerValue == 0)
                {
                    TurnOn(RelayName::TemperatureRelay3);
                }
            }
        }
    }
    
    bool RelayManager::GetApplicationState( void )
    {
        return _isApplicationRunning;
    }

    void RelayManager::StartManagingRelays( void )
    {
        _isApplicationRunning = true;
    }

};