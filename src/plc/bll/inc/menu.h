#ifndef MENU_H_
#define MENU_H_

#include "../../hal/inc/lcd.h"
#include "../inc/relay_settings.h"
#include "../inc/system_time.h"

namespace bll
{

class CustomCharaters
{
public:

	typedef enum
	{
		DegreeSign = 8,
		NextSign,
		PreviousSign,
		UpSign,
		DownSign
	} ECustomCharaters;
};

class Menu;
typedef void (Menu::*MenuHandler)( void );
void RequestRefreshLcd( void );

class Menu
{
private:

	Menu( void );

	static Menu* _instance;

	unsigned char _menuIndex;

	static const unsigned char TotalMenu = 8;

	RelaySettings* _defaultRelaySettings;

	RelaySettings* _newRelaySettings;

	volatile unsigned char* _autoStartTimeOutValue;

	char _lcdStringLine[4][21];

	volatile bool _lcdRefreshRequested;

	MenuHandler _menuHandlers[TotalMenu];

	void ShowCommonMenu(bool isStart, int number, bool canGoBackward = true, bool canGoForward = true);

	void ShowIntervalMenu( void );

	void ShowKeepOnTimeMenu( void );

	void ShowStartTime2Menu( void );

	void ShowEndTime2Menu( void );

	void ShowConfirmationMenu( void );

	void ShowStartOrConfigureMenu( void );

	void ShowDefaultMenu( void );

	void ShowSetSystemTimeMenu (void );

	void RefreshLcd( void );

	RelayTime* _temporarySystemTime;

	SystemTime* _systemTime;

public:

	static Menu* GetInstance( void );

	void SetRelaySettings( RelaySettings* defaultRelaySettings, RelaySettings* newRelaySettings, RelayTime* temporarySystemTime, volatile unsigned char* autoStartTimeOutValue );

	void SetMenuMode( unsigned char menuIndex );

	void ShowFirmwareVersionMenu( void );

	void Show( void );

	friend void RequestRefreshLcd( void );

};
};

#endif
