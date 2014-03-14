#include "../inc/system_time.h"
#include "../inc/task_dispatcher.h"

namespace bll
{

SystemTime* SystemTime::_instance = NULL;

SystemTime::SystemTime( void )
{
	_hour = 0;
	_displayHour = 12;
	
	_minute = 0;
	_second = 0;
	
	_amPmChar = 'A';				

	TaskDispatcher::GetInstance()->AddTask(FriendUpdateTime);
}

SystemTime* SystemTime::GetInstance( void )
{
	if (_instance == NULL)
	{
		static SystemTime obj;
		_instance = &obj;
	}

	return _instance;
}

int SystemTime::GetHour( void )
{
	return _displayHour;
}

int SystemTime::GetMinute( void )
{
	return _minute;
}

int SystemTime::GetSecond( void )
{
	return _second;
}

int SystemTime::GetAmPmChar( void )
{
	return _amPmChar;
}

void SystemTime::UpdateTime( void )
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

	_second++;
	if(_second > 59){
		_second = 0;
		_minute++;
		if(_minute > 59){
			_hour++;
			if(_hour > 23){
				_hour = 0;
			}

			// Format display hour in 12 hour format
			_displayHour = _hour;
			if (_displayHour >= 12) {
				_amPmChar = 'P';
				if( _displayHour > 12){
					_displayHour -= 12;
				}
			} else {
				_amPmChar = 'A';
				if (_displayHour == 0) {
					_displayHour = 12;
				}
			}
		}
	}
}

int SystemTime::GetTimeValueInMinutes( void )
{
	return _hour * 60 + _minute;
}

void FriendUpdateTime(void)
{
	SystemTime::_instance->UpdateTime();
}
};
