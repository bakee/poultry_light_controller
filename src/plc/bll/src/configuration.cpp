#include "../inc/configuration.h"
#include "../inc/task_dispatcher.h"

#ifndef NULL
#define NULL 0
#endif

#define MAXIMUM_MINUTES 1439 // 11:59 PM
#define MINIMUM_MINUTES 0 // 12:00 AM


namespace bll
{

using namespace hal;

Configuration* Configuration::_instance = NULL;

Configuration::Configuration( void )
{
	_autoStartTimeOutValue = MenuTimeoutValue;

	_menu = Menu::GetInstance();

	// Set temporary time at 12:00:00 AM
	_temporarySystemTime.totalMinutes = 0;
	_temporarySystemTime.displayHour = 12;
	_temporarySystemTime.displayMinute = 0;
	_temporarySystemTime.isDisplayTimeInPm = 0;

	_menu->SetRelaySettings(&_relaySettings, &_temporaryRelaySettings, &_temporarySystemTime, &_autoStartTimeOutValue);

	_systemTime = SystemTime::GetInstance();

	_relayManager = RelayManager::GetInstance();

	GetDefaultValues();
	_temporaryRelaySettings = _relaySettings;
	_relayManager->SetRelaySettings(&_relaySettings);

	_eeprom = Eeprom::GetInstance();


	_increaseHandler[0] = &Configuration::IncreaseStartTime1Value;
	_increaseHandler[1] = &Configuration::IncreaseEndTime1Value;
	_increaseHandler[2] = &Configuration::IncreaseStartTime2Value;
	_increaseHandler[3] = &Configuration::IncreaseEndTime2Value;
	_increaseHandler[4] = &Configuration::SaveChanges;

	_decreaseHandler[0] = &Configuration::DecreaseStartTime1Value;
	_decreaseHandler[1] = &Configuration::DecreaseEndTime1Value;
	_decreaseHandler[2] = &Configuration::DecreaseStartTime2Value;
	_decreaseHandler[3] = &Configuration::DecreaseEndTime2Value;
	_decreaseHandler[4] = &Configuration::DiscardChanges;

	_state = NumberOfState;
	_menuTimeout = 0;

	// Initially system time is set, so the buttons should change the values to set the time
	_isSystemTimeSet = false;
	_onIncrease = &Configuration::IncreaseTemporarySystemTime;
	_onDecrease = &Configuration::DecreaseTemporarySystemTime;

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
	if(false == _isSystemTimeSet){
		SetSystemTime();
		_isSystemTimeSet = true;
		_menu->SetMenuMode(NumberOfState + 1);
		return;
	}
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
				(		   _temporaryRelaySettings.relayTimes[0].totalMinutes == _relaySettings.relayTimes[0].totalMinutes
						&& _temporaryRelaySettings.relayTimes[1].totalMinutes == _relaySettings.relayTimes[1].totalMinutes
						&& _temporaryRelaySettings.relayTimes[2].totalMinutes == _relaySettings.relayTimes[2].totalMinutes
						&& _temporaryRelaySettings.relayTimes[3].totalMinutes == _relaySettings.relayTimes[3].totalMinutes)) // No changes have been made
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
	if(false == _isSystemTimeSet){
		return;
	}
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

void Configuration::FormatDisplayTime(RelayTime *relayTime) {

	unsigned int temporaryDisplayHour = ((unsigned int)relayTime->totalMinutes) / 60;
	if (temporaryDisplayHour >= 12) {
		relayTime->isDisplayTimeInPm = 1;
		if( temporaryDisplayHour > 12){
			temporaryDisplayHour -= 12;
		}
	} else {
		relayTime->isDisplayTimeInPm = 0;
		if (temporaryDisplayHour == 0) {
			temporaryDisplayHour = 12;
		}
	}

	relayTime->displayHour = temporaryDisplayHour;
	relayTime->displayMinute = relayTime->totalMinutes % 60;
}

unsigned char Configuration::GetIncrementDecrementAmount(
		IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType) {
	unsigned char incrementAmount = 0;
	switch (increaseDecreaseType) {
	case IncreaseDecreaseType::Fast:
		incrementAmount = 10;
		break;
	case IncreaseDecreaseType::Faster:
		incrementAmount = 60;
		break;
	default:
	case IncreaseDecreaseType::Normal:
		incrementAmount = 1;
		break;
	}
	return incrementAmount;
}

void Configuration::IncreaseTimeValue(IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType, int number){
	unsigned char incrementAmount = GetIncrementDecrementAmount(increaseDecreaseType);

	_temporaryRelaySettings.relayTimes[number].totalMinutes += incrementAmount;

	if (_temporaryRelaySettings.relayTimes[number].totalMinutes > MAXIMUM_MINUTES)
	{
		_temporaryRelaySettings.relayTimes[number].totalMinutes = MAXIMUM_MINUTES;
	}

	FormatDisplayTime(&_temporaryRelaySettings.relayTimes[number]);
}

void Configuration::DecreaseTimeValue(IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType, int number){
	unsigned char decrementAmount = GetIncrementDecrementAmount(increaseDecreaseType);

	if (_temporaryRelaySettings.relayTimes[number].totalMinutes <= (decrementAmount + (unsigned int)MINIMUM_MINUTES))
	{
		_temporaryRelaySettings.relayTimes[number].totalMinutes = MINIMUM_MINUTES;
	}
	else
	{
		_temporaryRelaySettings.relayTimes[number].totalMinutes -= decrementAmount;
	}

	FormatDisplayTime(&_temporaryRelaySettings.relayTimes[number]);
}

void Configuration::IncreaseStartTime1Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
{
	IncreaseTimeValue(increaseDecreaseType, 0);
}

void Configuration::IncreaseEndTime1Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
{
	IncreaseTimeValue(increaseDecreaseType, 1);
}

void Configuration::IncreaseStartTime2Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
{
	IncreaseTimeValue(increaseDecreaseType, 2);
}

void Configuration::IncreaseEndTime2Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
{
	IncreaseTimeValue(increaseDecreaseType, 3);
}

void Configuration::IncreaseTemporarySystemTime( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
{
	unsigned char incrementAmount = 0;
	switch (increaseDecreaseType) {
	case IncreaseDecreaseType::Fast:
		incrementAmount = 10;
		break;
	case IncreaseDecreaseType::Faster:
		incrementAmount = 60;
		break;
	default:
	case IncreaseDecreaseType::Normal:
		incrementAmount = 1;
		break;
	}

	_temporarySystemTime.totalMinutes += incrementAmount;

	if(_temporarySystemTime.totalMinutes > MAXIMUM_MINUTES){
		_temporarySystemTime.totalMinutes = MAXIMUM_MINUTES;
	}

	FormatDisplayTime(&_temporarySystemTime);
}

void Configuration::DecreaseStartTime1Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
{
	DecreaseTimeValue(increaseDecreaseType, 0);
}

void Configuration::DecreaseEndTime1Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
{
	DecreaseTimeValue(increaseDecreaseType, 1);
}

void Configuration::DecreaseStartTime2Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
{
	DecreaseTimeValue(increaseDecreaseType, 2);
}

void Configuration::DecreaseEndTime2Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
{
	DecreaseTimeValue(increaseDecreaseType, 3);
}

void Configuration::DecreaseTemporarySystemTime( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType )
{
	unsigned char decrementAmount = 0;
	switch (increaseDecreaseType) {
	case IncreaseDecreaseType::Fast:
		decrementAmount = 10;
		break;
	case IncreaseDecreaseType::Faster:
		decrementAmount = 60;
		break;
	default:
	case IncreaseDecreaseType::Normal:
		decrementAmount = 1;
		break;
	}

	if (_temporarySystemTime.totalMinutes <= (decrementAmount + (unsigned int)MINIMUM_MINUTES))
	{
		_temporarySystemTime.totalMinutes = MINIMUM_MINUTES;
	}
	else
	{
		_temporarySystemTime.totalMinutes -= decrementAmount;
	}

	FormatDisplayTime(&_temporarySystemTime);
}

void Configuration::SetSystemTime(){
	_systemTime->SetTime(&_temporarySystemTime);
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
			readCheckSum != calculatedCheckSum
			|| _relaySettings.relayTimes[0].totalMinutes > MAXIMUM_MINUTES
			|| _relaySettings.relayTimes[1].totalMinutes > MAXIMUM_MINUTES
			|| _relaySettings.relayTimes[2].totalMinutes > MAXIMUM_MINUTES
			|| _relaySettings.relayTimes[3].totalMinutes > MAXIMUM_MINUTES
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

		_relaySettings.relayTimes[0].totalMinutes = 180; // 3:00 AM
		_relaySettings.relayTimes[1].totalMinutes = 360; // 6:00 AM
		_relaySettings.relayTimes[2].totalMinutes = 1140; // 7:00 PM
		_relaySettings.relayTimes[3].totalMinutes = 1320; // 10:00 PM
		
		for(int i = 0; i < 4; ++i){
			FormatDisplayTime(&_relaySettings.relayTimes[i]);
		}
		
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
	// If the system time is not set, then do not count down
	if( false == _isSystemTimeSet){
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
