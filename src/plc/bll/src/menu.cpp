#include "../inc/menu.h"
#include "../inc/task_dispatcher.h"
#include <stdio.h>

namespace bll
{
using namespace hal;

Menu* Menu::_instance = NULL;

unsigned char customChars[] = {
		0x07, 0x05, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, // DegreeSign
		0x18, 0x1C, 0x1E, 0x1F, 0x1E, 0x1C, 0x18, 0x00, // NextSign
		0x03, 0x07, 0x0F, 0x1F, 0x0F, 0x07, 0x03, 0x00, // PreviousSign
		0x04, 0x0E, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, // UpSign
		0x00, 0x00, 0x00, 0x1F, 0x1F, 0x0E, 0x04, 0x00 // DownSign
};

Menu::Menu( void )
{
	_defaultRelaySettings = NULL;
	_newRelaySettings = NULL;
	_autoStartTimeOutValue = NULL;
	_menuIndex = TotalMenu - 1;

	_menuHandlers[0] = &Menu::ShowStartTime1Menu;
	_menuHandlers[1] = &Menu::ShowEndTime1Menu;
	_menuHandlers[2] = &Menu::ShowStartTime2Menu;
	_menuHandlers[3] = &Menu::ShowEndTime2Menu;
	_menuHandlers[4] = &Menu::ShowConfirmationMenu;
	_menuHandlers[5] = &Menu::ShowDefaultMenu;
	_menuHandlers[6] = &Menu::ShowStartOrConfigureMenu;
	_menuHandlers[7] = &Menu::ShowSetSystemTimeMenu;

	Lcd::GetInstance()->DefineCustomCharacter(0, customChars, 5);
	TaskDispatcher::GetInstance()->AddTask(RequestRefreshLcd);
	_lcdRefreshRequested = false;

	_systemTime = SystemTime::GetInstance();
}

Menu* Menu::GetInstance( void )
{
	if (_instance == NULL)
	{
		static Menu object;
		_instance = &object;
	}

	return _instance;
}

void Menu::Show( void )
{
	if (_defaultRelaySettings == NULL || _newRelaySettings == NULL)
	{
		return;
	}

	RefreshLcd();

	(this->*(_menuHandlers[_menuIndex]))();

	Lcd* lcd = Lcd::GetInstance();

	for (unsigned char i = 0; i < 4; ++i)
	{
		lcd->Goto(0, i);
		lcd->SendString(_lcdStringLine[i]);
	}
}

void Menu::SetRelaySettings( RelaySettings* defaultRelaySettings, RelaySettings* newRelaySettings, RelayTime* temporarySystemTime, volatile unsigned char* autoStartTimeOutValue )
{
	_defaultRelaySettings = defaultRelaySettings;
	_newRelaySettings = newRelaySettings;
	_autoStartTimeOutValue = autoStartTimeOutValue;
	_temporarySystemTime = temporarySystemTime;
}

void Menu::SetMenuMode( unsigned char menuIndex )
{
	_menuIndex = menuIndex;
}

void Menu::ShowCommonMenu(bool isStart, int number, bool canGoBackward, bool canGoForward) {
	if(isStart)
	{
		sprintf(_lcdStringLine[0], "   Start Time: %d", number);
	}else
	{
		sprintf(_lcdStringLine[0], "   End Time: %d", number);
	}

	sprintf(_lcdStringLine[1], "Curr. Value: %02d:%02d%cM", _defaultRelaySettings->relayTimes[number - 1].displayHour, _defaultRelaySettings->relayTimes[number - 1].displayMinute, _defaultRelaySettings->relayTimes[number - 1].isDisplayTimeInPm);
	sprintf(_lcdStringLine[2], "New   Value: %02d:%02d%cM", _newRelaySettings->relayTimes[number - 1].displayHour, _newRelaySettings->relayTimes[number - 1].displayMinute, (char)_defaultRelaySettings->relayTimes[number - 1].isDisplayTimeInPm);
	if (*_autoStartTimeOutValue == 0) // This indicates application is running so no "+" or "-" needs to be shown since plus and minus buttons are disabled
	{
		sprintf(_lcdStringLine[3], "%c                  %c", canGoBackward ? (char) ((CustomCharaters::PreviousSign)) : ' ', canGoForward ? (char) ((CustomCharaters::NextSign)) : ' ');
	}
	else
	{
		sprintf(_lcdStringLine[3], "%c      -    +      %c", canGoBackward ? (char) ((CustomCharaters::PreviousSign)) : ' ', canGoForward ? (char) ((CustomCharaters::NextSign)) : ' ');
	}
}

void Menu::ShowStartTime1Menu( void )
{
	ShowCommonMenu(true, 1, false);
}

void Menu::ShowEndTime1Menu( void )
{
	ShowCommonMenu(false, 2);
}

void Menu::ShowStartTime2Menu( void )
{
	ShowCommonMenu(true, 3);
}

void Menu::ShowEndTime2Menu( void )
{
	ShowCommonMenu(false, 4, true, false);
}

void Menu::ShowConfirmationMenu( void )
{
	sprintf(_lcdStringLine[0],"    Confirmation");
	sprintf(_lcdStringLine[1],"Do You want to save");
	sprintf(_lcdStringLine[2],"the changes ?");
	sprintf(_lcdStringLine[3],"%c      N    Y       ", (char)(CustomCharaters::PreviousSign));
}

void Menu::ShowStartOrConfigureMenu( void )
{
	sprintf(_lcdStringLine[0],"Start or Configure ?");
	sprintf(_lcdStringLine[1]," ");
	sprintf(_lcdStringLine[2],"Auto Start in %02d sec", *_autoStartTimeOutValue);
	sprintf(_lcdStringLine[3],"Start      Configure");
}

void Menu::ShowSetSystemTimeMenu( void )
{
	sprintf(_lcdStringLine[0],"  Set System Time");
	sprintf(_lcdStringLine[1]," ");
	sprintf(_lcdStringLine[2],"  Time: %02d:%02d %cM", _temporarySystemTime->displayHour, _temporarySystemTime->displayMinute, _temporarySystemTime->isDisplayTimeInPm == 0 ? 'A' : 'P');
	sprintf(_lcdStringLine[3],"       -    +     OK");
}

void Menu::ShowDefaultMenu( void )
{
	sprintf(_lcdStringLine[0],"  LIGHT CONTROLLER");
	sprintf(_lcdStringLine[1]," ");
	sprintf(_lcdStringLine[2],"Mobile: 01714228422");
	sprintf(_lcdStringLine[3],"  Time: %02d:%02d:%02d %cM", _systemTime->GetHour(), _systemTime->GetMinute(), _systemTime->GetSecond(), _systemTime->GetAmPmChar());
}

void Menu::ShowFirmwareVersionMenu( void )
{
	sprintf(_lcdStringLine[0],"      PSolvers");
	sprintf(_lcdStringLine[1],"  Light Controller");
	sprintf(_lcdStringLine[2],"    Version: 1.0");
	sprintf(_lcdStringLine[3],"  www.psolvers.com");

	Lcd* lcd = Lcd::GetInstance();

	lcd->Clear();

	for (unsigned char i = 0; i < 4; ++i)
	{
		lcd->Goto(0, i);
		lcd->SendString(_lcdStringLine[i]);
	}
}

void Menu::RefreshLcd( void )
{
	if(!_lcdRefreshRequested)
	{
		return;
	}

	_lcdRefreshRequested = false;

	static unsigned char loop = 0;
	loop++;
	if(loop < TaskDispatcher::GetInterruptRate() * 10) // Refresh after 10 seconds
			{
		return;
			}
	else
	{
		loop = 0;
	}

	Lcd::GetInstance()->Refresh();
	Lcd::GetInstance()->DefineCustomCharacter(0, customChars, 5);
}

void RequestRefreshLcd( void )
{
	Menu::_instance->_lcdRefreshRequested = true;
}
};
