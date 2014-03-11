#include "../inc/configuration.h"
#include "../inc/task_dispatcher.h"

#ifndef NULL
#define NULL 0
#endif

#define START_TIME_1_HOUR_VALUE 3 // 3 for 03:xx AM
#define START_TIME_1_MINUTE_VALUE 0 // 0 for xx:00 XM

#define END_TIME_1_HOUR_VALUE 6 // 6 for 06:xx AM
#define END_TIME_1_MINUTE_VALUE 0 // 0 for xx:00 XM

#define START_TIME_2_HOUR_VALUE 17 // 17 for 05:xx PM
#define START_TIME_2_MINUTE_VALUE 00 // 0 for xx:00 XM

#define END_TIME_2_HOUR_VALUE 21 // 21 for 09:xx PM
#define END_TIME_2_MINUTE_VALUE 0 // 0 for xx:00 XM

namespace bll
{
    
    using namespace hal;
    
    Configuration* Configuration::_instance = NULL;

    Configuration::Configuration( void )
    {
        _autoStartTimeOutValue = MenuTimeoutValue;
        
        _menu = Menu::GetInstance();
        _menu->SetRelaySettings(&_relaySettings, &_temporaryRelaySettings, &_autoStartTimeOutValue);
        
        _relayManager = RelayManager::GetInstance();
        
        GetDefaultValues();
        _temporaryRelaySettings = _relaySettings;
        _relayManager->SetRelaySettings(&_relaySettings);
        
        _eeprom = Eeprom::GetInstance();
        _onIncrease = NULL;
        _onDecrease = NULL;
        
        _increaseHandler[0] = &Configuration::IncreaseDefaultTemperature;
        _increaseHandler[1] = &Configuration::IncreaseTemperatureRelay2Interval;
        _increaseHandler[2] = &Configuration::IncreaseTemperatureRelay3Interval;
        _increaseHandler[3] = &Configuration::IncreaseDefaultHumidity;
        _increaseHandler[4] = &Configuration::IncreaseTimer1RelayInterval;
        _increaseHandler[5] = &Configuration::IncreaseTimer2RelayInterval;
        _increaseHandler[6] = &Configuration::IncreaseTimer2TurnOntime;
        //_increaseHandler[7] = &Configuration::IncreaseDefaultOxygenLevel;
        _increaseHandler[7] = &Configuration::SaveChanges;
        
        _decreaseHandler[0] = &Configuration::DecreaseDefaultTemperature;
        _decreaseHandler[1] = &Configuration::DecreaseTemperatureRelay2Interval;
        _decreaseHandler[2] = &Configuration::DecreaseTemperatureRelay3Interval;
        _decreaseHandler[3] = &Configuration::DecreaseDefaultHumidity;
        _decreaseHandler[4] = &Configuration::DecreaseTimer1RelayInterval;
        _decreaseHandler[5] = &Configuration::DecreaseTimer2RelayInterval;
        _decreaseHandler[6] = &Configuration::DecreaseTimer2TurnOntime;
        //_decreaseHandler[7] = &Configuration::DecreaseDefaultOxygenLevel;
        _decreaseHandler[7] = &Configuration::DiscardChanges;
        
        _state = NumberOfState;
        _menuTimeout = 0;
        
        TaskDispatcher::GetInstance()->AddTask(FriendDecrementConfigurationTimeout);
    }

    Configuration* Configuration::GetInstance( void )
    {
        if(_instance == NULL)
        {
            static Configuration object;
            _instance = &object;
        }
        
        return _instance;
    }
    
    void Configuration::IncreaseValue( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        if(_relayManager->GetApplicationState())
        {
            return;
        }
        
        if (_onIncrease != NULL)
        {
            RefreshMenuTimeout();
            
            (this->*_onIncrease)(increaseDecreaseType);
        }
    }

    void Configuration::DecreaseValue( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        if(_relayManager->GetApplicationState())
        {
            return;
        }
        
        if (_onDecrease != NULL)
        {
            RefreshMenuTimeout();
            
            (this->*_onDecrease)(increaseDecreaseType);
        }
    }

    void Configuration::SetNextEventHandler()
    {
        RefreshMenuTimeout();
        
        if (_state == NumberOfState - 1) // Confirmation state
        {
            return; // Do nothing, this button is disabled
        }
        else if(_state == NumberOfState) // Default state
        {
            _state = 0; // Set to first configuration menu
        }
        else if(_state == NumberOfState - 2) // Before confirmation state
        {
            if(_relayManager->GetApplicationState() == true || // Either application is running or
            (_temporaryRelaySettings.defaultHumidity == _relaySettings.defaultHumidity
            && _temporaryRelaySettings.defaultOxygenLevel == _relaySettings.defaultOxygenLevel
            && _temporaryRelaySettings.defaultTemperature == _relaySettings.defaultTemperature
            && _temporaryRelaySettings.temperatureRelay2Interval == _relaySettings.temperatureRelay2Interval
            && _temporaryRelaySettings.temperatureRelay3Interval == _relaySettings.temperatureRelay3Interval
            && _temporaryRelaySettings.timer1RelayInterval == _relaySettings.timer1RelayInterval
            && _temporaryRelaySettings.timer2RelayInterval == _relaySettings.timer2RelayInterval
            && _temporaryRelaySettings.timer2TurnOntime == _relaySettings.timer2TurnOntime)) // No changes have been made
            {
                SetToDefaultState();
            }
            else
            {
                _state++; // Move to confirmation state
            }
        }
        else
        {
            _state++; // Move to next configuration menu
        }
        
        _onIncrease = _increaseHandler[_state];
        _onDecrease = _decreaseHandler[_state];
        
        if(_state == NumberOfState)
        {
            SetToDefaultState();
        }
        else
        {
            _menu->SetMenuMode(_state);
        }
    }

    void Configuration::SetPreviousEventHandler()
    {
        RefreshMenuTimeout();
        
        if(_relayManager->GetApplicationState() == false && _state == NumberOfState) // Application is not running
        {
            _autoStartTimeOutValue = 0;
            _relayManager->StartManagingRelays();
            SetToDefaultState();
            return;
        }
        
        if(_state == NumberOfState || _state == 0) // Default state, disable this button
        {
            return;
        }
        else if(_state == 0)
        {
            SetToDefaultState();
        }
        else
        {
            _state--;
            _onIncrease = _increaseHandler[_state];
            _onDecrease = _decreaseHandler[_state];
        }
        
        _menu->SetMenuMode(_state);
    }

    void Configuration::IncreaseDefaultTemperature( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char incrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            incrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            incrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            incrementAmount = 1;
            break;
        }
        
        _temporaryRelaySettings.defaultTemperature += incrementAmount;
        
        if (_temporaryRelaySettings.defaultTemperature > DEFAULT_TEMPERATURE_HIGHEST_VALUE)
        {
            _temporaryRelaySettings.defaultTemperature = DEFAULT_TEMPERATURE_HIGHEST_VALUE;
        }
    }

    void Configuration::IncreaseTemperatureRelay2Interval( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char incrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            incrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            incrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            incrementAmount = 1;
            break;
        }
        
        _temporaryRelaySettings.temperatureRelay2Interval += incrementAmount;
        
        if (_temporaryRelaySettings.temperatureRelay2Interval > TEMPERATURE_RELAY2_HIGHEST_VALUE)
        {
            _temporaryRelaySettings.temperatureRelay2Interval = TEMPERATURE_RELAY2_HIGHEST_VALUE;
        }
    }

    void Configuration::IncreaseTemperatureRelay3Interval( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char incrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            incrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            incrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            incrementAmount = 1;
            break;
        }
        
        _temporaryRelaySettings.temperatureRelay3Interval += incrementAmount;
        
        if (_temporaryRelaySettings.temperatureRelay3Interval > TEMPERATURE_RELAY3_HIGHEST_VALUE)
        {
            _temporaryRelaySettings.temperatureRelay3Interval = TEMPERATURE_RELAY3_HIGHEST_VALUE;
        }
    }

    void Configuration::IncreaseDefaultHumidity( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char incrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            incrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            incrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            incrementAmount = 1;
            break;
        }
        
        _temporaryRelaySettings.defaultHumidity += incrementAmount;
        
        
        if (_temporaryRelaySettings.defaultHumidity > DEFAULT_HUMIDITY_HIGHEST_VALUE)
        {
            _temporaryRelaySettings.defaultHumidity = DEFAULT_HUMIDITY_HIGHEST_VALUE;
        }
    }

    void Configuration::IncreaseTimer1RelayInterval( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char incrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            incrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            incrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            incrementAmount = 1;
            break;
        }
        
        _temporaryRelaySettings.timer1RelayInterval += incrementAmount;
        
        if (_temporaryRelaySettings.timer1RelayInterval > TIMER1_RELAY_INTERVAL_HIGHEST_VALUE)
        {
            _temporaryRelaySettings.timer1RelayInterval = TIMER1_RELAY_INTERVAL_HIGHEST_VALUE;
        }
    }

    void Configuration::IncreaseTimer2RelayInterval( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char incrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            incrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            incrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            incrementAmount = 1;
            break;
        }
        
        _temporaryRelaySettings.timer2RelayInterval += incrementAmount;
        
        if (_temporaryRelaySettings.timer2RelayInterval > TIMER2_RELAY_INTERVAL_HIGHEST_VALUE)
        {
            _temporaryRelaySettings.timer2RelayInterval = TIMER2_RELAY_INTERVAL_HIGHEST_VALUE;
        }
    }

    void Configuration::IncreaseTimer2TurnOntime( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char incrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            incrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            incrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            incrementAmount = 1;
            break;
        }
        
        _temporaryRelaySettings.timer2TurnOntime += incrementAmount;
        
        if (_temporaryRelaySettings.timer2TurnOntime > TIMER2_TURN_ON_TIME_HIGHEST_VALUE)
        {
            _temporaryRelaySettings.timer2TurnOntime = TIMER2_TURN_ON_TIME_HIGHEST_VALUE;
        }
    }

    void Configuration::IncreaseDefaultOxygenLevel( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char incrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            incrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            incrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            incrementAmount = 1;
            break;
        }
        
        _temporaryRelaySettings.defaultOxygenLevel += incrementAmount;
        
        if (_temporaryRelaySettings.defaultOxygenLevel > DEFAULT_OXYGEN_LEVEL_HIGHEST_VALUE)
        {
            _temporaryRelaySettings.defaultOxygenLevel = DEFAULT_OXYGEN_LEVEL_HIGHEST_VALUE;
        }
    }

    void Configuration::DecreaseDefaultTemperature( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char decrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            decrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            decrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            decrementAmount = 1;
            break;
        }
        
        if (_temporaryRelaySettings.defaultTemperature <= (decrementAmount + (unsigned int)DEFAULT_TEMPERATURE_LOWEST_VALUE))
        {
            _temporaryRelaySettings.defaultTemperature = DEFAULT_TEMPERATURE_LOWEST_VALUE;
        }
        else
        {
            _temporaryRelaySettings.defaultTemperature -= decrementAmount;
        }
    }

    void Configuration::DecreaseTemperatureRelay2Interval( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char decrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            decrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            decrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            decrementAmount = 1;
            break;
        }
        
        if (_temporaryRelaySettings.temperatureRelay2Interval <= (decrementAmount + (unsigned int)TEMPERATURE_RELAY2_LOWEST_VALUE))
        {
            _temporaryRelaySettings.temperatureRelay2Interval = TEMPERATURE_RELAY2_LOWEST_VALUE;
        }
        else
        {
            _temporaryRelaySettings.temperatureRelay2Interval -= decrementAmount;
        }
    }

    void Configuration::DecreaseTemperatureRelay3Interval( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char decrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            decrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            decrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            decrementAmount = 1;
            break;
        }
        
        if (_temporaryRelaySettings.temperatureRelay3Interval <= (decrementAmount + (unsigned int)TEMPERATURE_RELAY3_LOWEST_VALUE))
        {
            _temporaryRelaySettings.temperatureRelay3Interval = TEMPERATURE_RELAY3_LOWEST_VALUE;
        }
        else
        {
            _temporaryRelaySettings.temperatureRelay3Interval -= decrementAmount;
        }
    }

    void Configuration::DecreaseDefaultHumidity( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char decrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            decrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            decrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            decrementAmount = 1;
            break;
        }
        
        if (_temporaryRelaySettings.defaultHumidity <= (decrementAmount + (unsigned int)DEFAULT_HUMIDITY_LOWEST_VALUE))
        {
            _temporaryRelaySettings.defaultHumidity = DEFAULT_HUMIDITY_LOWEST_VALUE;
        }
        else
        {
            _temporaryRelaySettings.defaultHumidity -= decrementAmount;
        }
    }

    void Configuration::DecreaseTimer1RelayInterval( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char decrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            decrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            decrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            decrementAmount = 1;
            break;
        }
        
        if (_temporaryRelaySettings.timer1RelayInterval <= (decrementAmount + (unsigned int)TIMER1_RELAY_INTERVAL_LOWEST_VALUE))
        {
            _temporaryRelaySettings.timer1RelayInterval = TIMER1_RELAY_INTERVAL_LOWEST_VALUE;
        }
        else
        {
            _temporaryRelaySettings.timer1RelayInterval -= decrementAmount;
        }
    }

    void Configuration::DecreaseTimer2RelayInterval( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char decrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            decrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            decrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            decrementAmount = 1;
            break;
        }
        
        if (_temporaryRelaySettings.timer2RelayInterval <= (decrementAmount + (unsigned int)TIMER2_RELAY_INTERVAL_LOWEST_VALUE))
        {
            _temporaryRelaySettings.timer2RelayInterval = TIMER2_RELAY_INTERVAL_LOWEST_VALUE;
        }
        else
        {
            _temporaryRelaySettings.timer2RelayInterval -= decrementAmount;
        }
    }

    void Configuration::DecreaseTimer2TurnOntime( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char decrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            decrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            decrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            decrementAmount = 1;
            break;
        }
        
        if (_temporaryRelaySettings.timer2TurnOntime <= (decrementAmount + (unsigned int)TIMER2_TURN_ON_TIME_LOWEST_VALUE))
        {
            _temporaryRelaySettings.timer2TurnOntime = TIMER2_TURN_ON_TIME_LOWEST_VALUE;
        }
        else
        {
            _temporaryRelaySettings.timer2TurnOntime -= decrementAmount;
        }
    }

    void Configuration::DecreaseDefaultOxygenLevel( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        unsigned char decrementAmount = 0;
        switch(increaseDecreaseType)
        {
            case IncreaseDecreaseType::Fast:
            decrementAmount = 10;
            break;
            case IncreaseDecreaseType::Faster:
            decrementAmount = 10;
            break;
            default:
            case IncreaseDecreaseType::Normal:
            decrementAmount = 1;
            break;
        }
        
        if (_temporaryRelaySettings.defaultOxygenLevel <= (decrementAmount + (unsigned int)DEFAULT_OXYGEN_LEVEL_LOWEST_VALUE))
        {
            _temporaryRelaySettings.defaultOxygenLevel = DEFAULT_OXYGEN_LEVEL_LOWEST_VALUE;
        }
        else
        {
            _temporaryRelaySettings.defaultOxygenLevel -= decrementAmount;
        }
    }
    
    void Configuration::SaveChanges( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        // If application is running this will not be executed, but for more safety (!), return
        if(_relayManager->GetApplicationState() == true)
        {
            return;
        }
        
        _relaySettings = _temporaryRelaySettings;
        WriteDefaultValuesToEeprom();
        SetToDefaultState();
        
        RefreshMenuTimeout();
    }

    void Configuration::DiscardChanges( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
    {
        _temporaryRelaySettings = _relaySettings;
        SetToDefaultState();
        if(_relayManager->GetApplicationState() == false)
        {
            RefreshMenuTimeout();
        }
    }
    
    bool Configuration::ReadDefaultValuesFromEeprom( void )
    {
        unsigned char calculatedCheckSum = 0x00;
        unsigned int eepromCheckSumAddress = 0x01;
        unsigned int startingMemoryAddress = 0x02;
        unsigned int dataMemoryPosition = (unsigned int)&_relaySettings;
        
        for (unsigned int i = 0; i < sizeof(RelaySettings); ++i)
        {
            *((unsigned char *)(dataMemoryPosition + i)) = _eeprom->Read(startingMemoryAddress + i);
            calculatedCheckSum += *((unsigned char *)(dataMemoryPosition + i));
        }
        
        unsigned char readCheckSum = _eeprom->Read(eepromCheckSumAddress);
        
        if(
        readCheckSum != calculatedCheckSum ||
        _relaySettings.defaultTemperature < DEFAULT_TEMPERATURE_LOWEST_VALUE || _relaySettings.defaultTemperature > DEFAULT_TEMPERATURE_HIGHEST_VALUE ||
        _relaySettings.temperatureRelay2Interval < TEMPERATURE_RELAY2_LOWEST_VALUE || _relaySettings.temperatureRelay2Interval > TEMPERATURE_RELAY2_HIGHEST_VALUE ||
        _relaySettings.temperatureRelay3Interval < TEMPERATURE_RELAY3_LOWEST_VALUE || _relaySettings.temperatureRelay3Interval > TEMPERATURE_RELAY3_HIGHEST_VALUE ||
        _relaySettings.defaultHumidity < DEFAULT_HUMIDITY_LOWEST_VALUE || _relaySettings.defaultHumidity > DEFAULT_HUMIDITY_HIGHEST_VALUE ||
        _relaySettings.timer1RelayInterval < TIMER1_RELAY_INTERVAL_LOWEST_VALUE || _relaySettings.timer1RelayInterval > TIMER1_RELAY_INTERVAL_HIGHEST_VALUE ||
        _relaySettings.timer2RelayInterval < TIMER2_RELAY_INTERVAL_LOWEST_VALUE || _relaySettings.timer2RelayInterval > TIMER2_RELAY_INTERVAL_HIGHEST_VALUE ||
        _relaySettings.timer2TurnOntime < TIMER2_TURN_ON_TIME_LOWEST_VALUE || _relaySettings.timer2TurnOntime > TIMER2_TURN_ON_TIME_HIGHEST_VALUE ||
        _relaySettings.defaultOxygenLevel < DEFAULT_OXYGEN_LEVEL_LOWEST_VALUE || _relaySettings.defaultOxygenLevel > DEFAULT_OXYGEN_LEVEL_HIGHEST_VALUE
        )
        {
            return false;
        }
        
        return true;
    }

    void Configuration::WriteDefaultValuesToEeprom( void )
    {
        unsigned char checkSum = 0x00;
        unsigned int eepromCheckSumAddress = 0x01;
        unsigned int startingMemoryAddress = 0x02;
        unsigned int dataMemoryPosition = (unsigned int)&_relaySettings;
        
        for (unsigned int i = 0; i < sizeof(RelaySettings); ++i)
        {
            checkSum += *((unsigned char *)(dataMemoryPosition + i));
            _eeprom->Write(startingMemoryAddress + i, *((unsigned char *)(dataMemoryPosition + i)));
        }
        
        _eeprom->Write(eepromCheckSumAddress, checkSum);
    }

    void Configuration::GetDefaultValues( void )
    {
        unsigned int eepromMagicByteAddress = 0x00;
        unsigned char eepromMagicByteValue = 64;
        
        if(_eeprom->Read(eepromMagicByteAddress) != eepromMagicByteValue || !ReadDefaultValuesFromEeprom())
        {
            _relaySettings.defaultTemperature = 995;
            _relaySettings.defaultHumidity = 600;
            _relaySettings.defaultOxygenLevel = 500;
            
            _relaySettings.temperatureRelay2Interval = 60;
            _relaySettings.temperatureRelay3Interval = 60;
            
            _relaySettings.timer1RelayInterval = 900;
            _relaySettings.timer2RelayInterval = 60; // in minute
            
            _relaySettings.timer2TurnOntime = 70;
            
            WriteDefaultValuesToEeprom();
            _eeprom->Write(eepromMagicByteAddress, eepromMagicByteValue);
        }
    }
    
    void Configuration::SetToDefaultState( void )
    {
        _onIncrease = NULL;
        _onDecrease = NULL;
        _state = NumberOfState;
        if(_relayManager->GetApplicationState())
        {
            _menu->SetMenuMode(_state);
        }
        else
        {
            _menu->SetMenuMode(_state + 1); // Run or Configuration Menu
            _autoStartTimeOutValue = MenuTimeoutValue;
        }
    }

    void Configuration::RefreshMenuTimeout( void )
    {
        _menuTimeout = MenuTimeoutValue;
    }

    void Configuration::DecrementConfigurationTimeout( void )
    {
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
        
        if(_relayManager->GetApplicationState()) // If application already running then handle _menuTimeout
        {
            if(_menuTimeout > 0)
            {
                _menuTimeout--;
                if(_menuTimeout == 0)
                {
                    _temporaryRelaySettings = _relaySettings;
                    SetToDefaultState();
                }
            }
        }
        else // If application is not running i.e. in configuration mode the handle _autoStartTimeOutValue
        {
            // Decrement only if default screen is shown and no button is pressed
            if(_state == NumberOfState && _autoStartTimeOutValue > 0)
            {
                _autoStartTimeOutValue--;
                if(_autoStartTimeOutValue == 0)
                {
                    _relayManager->StartManagingRelays();
                    SetToDefaultState();
                }
            }
        }
    }

    void FriendDecrementConfigurationTimeout( void )
    {
        Configuration::_instance->DecrementConfigurationTimeout();
    }
};