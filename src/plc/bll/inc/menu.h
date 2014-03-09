/*
* menu.h
*
* Created: 1/19/2013 8:52:11 PM
*  Author: muhammad
*/

#ifndef MENU_H_
#define MENU_H_

#include "../../hal/inc/lcd.h"
#include "../inc/sensor.h"
#include "../inc/relay_settings.h"

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
        
        static const unsigned char TotalMenu = 10;
        
        RelaySettings* _defaultRelaySettings;
        
        RelaySettings* _newRelaySettings;
        
        volatile unsigned char* _autoStartTimeOutValue;
        
        char _lcdStringLine[4][21];

        volatile bool _lcdRefreshRequested;
        
        MenuHandler _menuHandlers[TotalMenu];
        
        void ShowDefaultTemperatureSetupMenu( void );
        
        void ShowTemperatureRelay2IntervalSetupMenu( void );
        
        void ShowTemperatureRelay3IntervalSetupMenu( void );
        
        void ShowDefaultHumiditySetupMenu( void );
        
        void ShowTimer1RelayIntervalSetupMenu( void );
        
        void ShowTimer2RelayIntervalSetupMenu( void );
        
        void ShowTimer2RelayTurnOntimeSetupMenu( void );
        
        void ShowDefaultOxygenLevelSetupMenu( void );
        
        void ShowConfirmationMenu( void );
        
        void ShowStartOrConfigureMenu( void );
        
        void ShowDefaultMenu( void );

        void RefreshLcd( void );
        
        public:
        
        static Menu* GetInstance( void );
        
        void SetRelaySettings( RelaySettings* defaultRelaySettings, RelaySettings* newRelaySettings, volatile unsigned char* autoStartTimeOutValue );
        
        void SetMenuMode( unsigned char menuIndex );
        
        void ShowFirmwareVersionMenu( void );
        
        void Show( void );        

        friend void RequestRefreshLcd( void );
        
    };
};

#endif /* MENU_H_ */