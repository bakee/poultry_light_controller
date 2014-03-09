/*
* menu.cpp
*
* Created: 1/19/2013 8:53:50 PM
*  Author: muhammad
*/

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
    
    //************************************
    // Method:    Menu
    // FullName:  bll::Menu::Menu
    // Access:    private
    // Returns:
    // Qualifier:
    // Parameter: void
    //************************************
    Menu::Menu( void )
    {
        _defaultRelaySettings = NULL;
        _newRelaySettings = NULL;
        _autoStartTimeOutValue = NULL;
        _menuIndex = TotalMenu - 1;
        
        _menuHandlers[0] = &Menu::ShowDefaultTemperatureSetupMenu;
        _menuHandlers[1] = &Menu::ShowTemperatureRelay2IntervalSetupMenu;
        _menuHandlers[2] = &Menu::ShowTemperatureRelay3IntervalSetupMenu;
        _menuHandlers[3] = &Menu::ShowDefaultHumiditySetupMenu;
        _menuHandlers[4] = &Menu::ShowTimer1RelayIntervalSetupMenu;
        _menuHandlers[5] = &Menu::ShowTimer2RelayIntervalSetupMenu;
        _menuHandlers[6] = &Menu::ShowTimer2RelayTurnOntimeSetupMenu;
        //_menuHandlers[7] = &Menu::ShowDefaultOxygenLevelSetupMenu;
        _menuHandlers[7] = &Menu::ShowConfirmationMenu;
        _menuHandlers[8] = &Menu::ShowDefaultMenu;
        _menuHandlers[9] = &Menu::ShowStartOrConfigureMenu;
        
        Lcd::GetInstance()->DefineCustomCharacter(0, customChars, 5);
        TaskDispatcher::GetInstance()->AddTask(RequestRefreshLcd);
        _lcdRefreshRequested = false;
    }

    //************************************
    // Method:    GetInstance
    // FullName:  bll::Menu::GetInstance
    // Access:    public static
    // Returns:   Menu*
    // Qualifier:
    // Parameter: void
    //************************************
    Menu* Menu::GetInstance( void )
    {
        if (_instance == NULL)
        {
            static Menu object;
            _instance = &object;
        }
        
        return _instance;
    }

    //************************************
    // Method:    Show
    // FullName:  bll::Menu::Show
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
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

    //************************************
    // Method:    SetRelaySettings
    // FullName:  bll::Menu::SetRelaySettings
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: RelaySettings * defaultRelaySettings
    // Parameter: RelaySettings * newRelaySettings
    //************************************
    void Menu::SetRelaySettings( RelaySettings* defaultRelaySettings, RelaySettings* newRelaySettings, volatile unsigned char* autoStartTimeOutValue )
    {
        _defaultRelaySettings = defaultRelaySettings;
        _newRelaySettings = newRelaySettings;
        _autoStartTimeOutValue = autoStartTimeOutValue;
    }

    void Menu::SetMenuMode( unsigned char menuIndex )
    {
        _menuIndex = menuIndex;
    }

    //************************************
    // Method:    ShowDefaultTemperatureSetupMenu
    // FullName:  bll::Menu::ShowDefaultTemperatureSetupMenu
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Menu::ShowDefaultTemperatureSetupMenu( void )
    {
        sprintf(_lcdStringLine[0],"Default Temperature");
        sprintf(_lcdStringLine[1],"Curr. Value: %3d.%d%cF", _defaultRelaySettings->defaultTemperature / 10, _defaultRelaySettings->defaultTemperature % 10, (char)(CustomCharaters::DegreeSign));
        sprintf(_lcdStringLine[2],"New   Value: %3d.%d%cF", _newRelaySettings->defaultTemperature / 10, _newRelaySettings->defaultTemperature % 10, (char)(CustomCharaters::DegreeSign));
        
        if(*_autoStartTimeOutValue == 0) // This indicates application is running so no "+" or "-" needs to be shown since plus and minus buttons are disabled
        {
            sprintf(_lcdStringLine[3],"                   %c", (char)(CustomCharaters::NextSign));
        }
        else
        {
            sprintf(_lcdStringLine[3],"       -    +      %c", (char)(CustomCharaters::NextSign));
        }
    }

    //************************************
    // Method:    ShowTemperatureRelay2IntervalSetupMenu
    // FullName:  bll::Menu::ShowTemperatureRelay2IntervalSetupMenu
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Menu::ShowTemperatureRelay2IntervalSetupMenu( void )
    {
        sprintf(_lcdStringLine[0],"  Relay2 Interval");
        sprintf(_lcdStringLine[1],"Curr. Value: 0:%02d:%02d", _defaultRelaySettings->temperatureRelay2Interval / 60, _defaultRelaySettings->temperatureRelay2Interval % 60);
        sprintf(_lcdStringLine[2],"New   Value: 0:%02d:%02d", _newRelaySettings->temperatureRelay2Interval / 60, _newRelaySettings->temperatureRelay2Interval % 60);
        
        if(*_autoStartTimeOutValue == 0) // This indicates application is running so no "+" or "-" needs to be shown since plus and minus buttons are disabled
        {
            sprintf(_lcdStringLine[3],"%c                  %c", (char)(CustomCharaters::PreviousSign), (char)(CustomCharaters::NextSign));
        }
        else
        {
            sprintf(_lcdStringLine[3],"%c      -    +      %c", (char)(CustomCharaters::PreviousSign), (char)(CustomCharaters::NextSign));
        }
    }

    //************************************
    // Method:    ShowTemperatureRelay3IntervalSetupMenu
    // FullName:  bll::Menu::ShowTemperatureRelay3IntervalSetupMenu
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Menu::ShowTemperatureRelay3IntervalSetupMenu( void )
    {
        sprintf(_lcdStringLine[0],"  Relay3 Interval");
        sprintf(_lcdStringLine[1],"Curr. Value: 0:%02d:%02d", _defaultRelaySettings->temperatureRelay3Interval / 60, _defaultRelaySettings->temperatureRelay3Interval % 60);
        sprintf(_lcdStringLine[2],"New   Value: 0:%02d:%02d", _newRelaySettings->temperatureRelay3Interval / 60, _newRelaySettings->temperatureRelay3Interval % 60);
        
        if(*_autoStartTimeOutValue == 0) // This indicates application is running so no "+" or "-" needs to be shown since plus and minus buttons are disabled
        {
            sprintf(_lcdStringLine[3],"%c                  %c", (char)(CustomCharaters::PreviousSign), (char)(CustomCharaters::NextSign));
        }
        else
        {
            sprintf(_lcdStringLine[3],"%c      -    +      %c", (char)(CustomCharaters::PreviousSign), (char)(CustomCharaters::NextSign));
        }
    }

    //************************************
    // Method:    ShowDefaultHumiditySetupMenu
    // FullName:  bll::Menu::ShowDefaultHumiditySetupMenu
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Menu::ShowDefaultHumiditySetupMenu( void )
    {
        sprintf(_lcdStringLine[0],"  Default Humidity");
        sprintf(_lcdStringLine[1],"Curr. Value: %3d.%d%%", _defaultRelaySettings->defaultHumidity / 10, _defaultRelaySettings->defaultHumidity % 10);
        sprintf(_lcdStringLine[2],"New   Value: %3d.%d%%", _newRelaySettings->defaultHumidity / 10, _newRelaySettings->defaultHumidity % 10);
        
        if(*_autoStartTimeOutValue == 0) // This indicates application is running so no "+" or "-" needs to be shown since plus and minus buttons are disabled
        {
            sprintf(_lcdStringLine[3],"%c                  %c", (char)(CustomCharaters::PreviousSign), (char)(CustomCharaters::NextSign));
        }
        else
        {
            sprintf(_lcdStringLine[3],"%c      -    +      %c", (char)(CustomCharaters::PreviousSign), (char)(CustomCharaters::NextSign));
        }
    }

    //************************************
    // Method:    ShowTimer1RelayIntervalSetupMenu
    // FullName:  bll::Menu::ShowTimer1RelayIntervalSetupMenu
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Menu::ShowTimer1RelayIntervalSetupMenu( void )
    {
        sprintf(_lcdStringLine[0],"  Timer-1 Interval");
        sprintf(_lcdStringLine[1],"Curr. Value: 0:%02d:%02d", _defaultRelaySettings->timer1RelayInterval / 60, _defaultRelaySettings->timer1RelayInterval % 60);
        sprintf(_lcdStringLine[2],"New   Value: 0:%02d:%02d", _newRelaySettings->timer1RelayInterval / 60, _newRelaySettings->timer1RelayInterval % 60);
        
        if(*_autoStartTimeOutValue == 0) // This indicates application is running so no "+" or "-" needs to be shown since plus and minus buttons are disabled
        {
            sprintf(_lcdStringLine[3],"%c                  %c", (char)(CustomCharaters::PreviousSign), (char)(CustomCharaters::NextSign));
        }
        else
        {
            sprintf(_lcdStringLine[3],"%c      -    +      %c", (char)(CustomCharaters::PreviousSign), (char)(CustomCharaters::NextSign));
        }
    }

    //************************************
    // Method:    ShowTimer2RelayIntervalSetupMenu
    // FullName:  bll::Menu::ShowTimer2RelayIntervalSetupMenu
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Menu::ShowTimer2RelayIntervalSetupMenu( void )
    {
        sprintf(_lcdStringLine[0],"  Timer-2 Interval");
        sprintf(_lcdStringLine[1],"Curr. Value: %02d:%02d", _defaultRelaySettings->timer2RelayInterval / 60, _defaultRelaySettings->timer2RelayInterval % 60);
        sprintf(_lcdStringLine[2],"New   Value: %02d:%02d", _newRelaySettings->timer2RelayInterval / 60, _newRelaySettings->timer2RelayInterval % 60);
        
        if(*_autoStartTimeOutValue == 0) // This indicates application is running so no "+" or "-" needs to be shown since plus and minus buttons are disabled
        {
            sprintf(_lcdStringLine[3],"%c                  %c", (char)(CustomCharaters::PreviousSign), (char)(CustomCharaters::NextSign));
        }
        else
        {
            sprintf(_lcdStringLine[3],"%c      -    +      %c", (char)(CustomCharaters::PreviousSign), (char)(CustomCharaters::NextSign));
        }
    }

    //************************************
    // Method:    ShowTimer2RelayTurnOntimeSetupMenu
    // FullName:  bll::Menu::ShowTimer2RelayTurnOntimeSetupMenu
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Menu::ShowTimer2RelayTurnOntimeSetupMenu( void )
    {
        sprintf(_lcdStringLine[0],"  Timer-2 On Time");
        sprintf(_lcdStringLine[1],"Curr. Value: 0:%02d:%02d", _defaultRelaySettings->timer2TurnOntime / 60, _defaultRelaySettings->timer2TurnOntime % 60);
        sprintf(_lcdStringLine[2],"New   Value: 0:%02d:%02d", _newRelaySettings->timer2TurnOntime / 60, _newRelaySettings->timer2TurnOntime % 60);
        
        if(*_autoStartTimeOutValue == 0) // This indicates application is running so no "+" or "-" needs to be shown since plus and minus buttons are disabled
        {
            sprintf(_lcdStringLine[3],"%c                  %c", (char)(CustomCharaters::PreviousSign), (char)(CustomCharaters::NextSign));
        }
        else
        {
            sprintf(_lcdStringLine[3],"%c      -    +      %c", (char)(CustomCharaters::PreviousSign), (char)(CustomCharaters::NextSign));
        }
    }

    //************************************
    // Method:    ShowDefaultOxygenLevelSetupMenu
    // FullName:  bll::Menu::ShowDefaultOxygenLevelSetupMenu
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Menu::ShowDefaultOxygenLevelSetupMenu( void )
    {
        sprintf(_lcdStringLine[0],"Default Oxygen Level");
        sprintf(_lcdStringLine[1],"Curr. Value: %3d.%d%%", _defaultRelaySettings->defaultOxygenLevel / 10, _defaultRelaySettings->defaultOxygenLevel % 10);
        sprintf(_lcdStringLine[2],"New   Value: %3d.%d%%", _newRelaySettings->defaultOxygenLevel / 10, _newRelaySettings->defaultOxygenLevel % 10);
        
        if(*_autoStartTimeOutValue == 0) // This indicates application is running so no "+" or "-" needs to be shown since plus and minus buttons are disabled
        {
            sprintf(_lcdStringLine[3],"%c                  %c", (char)(CustomCharaters::PreviousSign), (char)(CustomCharaters::NextSign));
        }
        else
        {
            sprintf(_lcdStringLine[3],"%c      -    +      %c", (char)(CustomCharaters::PreviousSign), (char)(CustomCharaters::NextSign));
        }
    }

    //************************************
    // Method:    ShowConfirmationMenu
    // FullName:  bll::Menu::ShowConfirmationMenu
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
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

    //************************************
    // Method:    ShowDefaultMenu
    // FullName:  bll::Menu::ShowDefaultMenu
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Menu::ShowDefaultMenu( void )
    {
        sprintf(_lcdStringLine[0],"  LIGHT CONTROLLER");
        sprintf(_lcdStringLine[1]," ");
        sprintf(_lcdStringLine[2],"Mobile: 01714228422");
        sprintf(_lcdStringLine[3]," ");
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