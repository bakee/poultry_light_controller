#include "../inc/relay_manager.h"

namespace bll
{
    using namespace hal;
    RelayManager* RelayManager::_instance = NULL;
    
    RelayManager::RelayManager()
    {
        _relay = Relay::GetInstance();
        
        _systemTime = SystemTime::GetInstance();

        _isApplicationRunning = false;
        
        _temperatureRelay2TimerValue = 0;
        _isTemperatureRelay2TimerEnabled = false;
        
        _temperatureRelay3TimerValue = 0;
        _isTemperatureRelay3TimerEnabled = false;        
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

        int currentTimeInMinutes = _systemTime->GetTimeValueInMinutes();
        if((currentTimeInMinutes >= _relaySettings->relayTimes[0].totalMinutes && currentTimeInMinutes < _relaySettings->relayTimes[1].totalMinutes)
		|| (currentTimeInMinutes >= _relaySettings->relayTimes[2].totalMinutes && currentTimeInMinutes < _relaySettings->relayTimes[3].totalMinutes)){
			TurnOn(RelayName::LightControllerRelay);
		}else{
			TurnOff(RelayName::LightControllerRelay);
		}
    }    

    void RelayManager::SetRelaySettings( RelaySettings* relaySettings )
    {
        _relaySettings = relaySettings;
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
