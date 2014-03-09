/*
* plc.cpp
*
* Created: 3/10/2014 12:40:37 AM
*  Author: muhammad
*/

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "hal/inc/led.h"
#include "hal/inc/lcd.h"
#include "hal/inc/timer0.h"

#include "bll/inc/display.h"
#include "bll/inc/relay_manager.h"
#include "bll/inc/button.h"
#include "bll/inc/menu.h"

void Toggle( void );
void Init( void );

using namespace bll;
using namespace hal;

int main()
{
    Init();
    
    RelayManager* relayManager = RelayManager::GetInstance();
    Menu* menu = Menu::GetInstance();
    Button::GetInstance();    
    Display* display = Display::GetInstance();

    sei();
    
    while(1)
    {                
        int timer2RemainingTime = relayManager->GetTimer2RemainingTime();
        
        if(relayManager->GetApplicationState())
        {
            display->Show(timer2RemainingTime, DisplayName::Timer);
            
            relayManager->ManageRelays();
        }
        
        menu->Show();

        Toggle();
    }
    
    return 0;
}

void Init()
{
    Menu::GetInstance()->ShowFirmwareVersionMenu();
    _delay_ms(4096);
}

void Toggle()
{
    Led::GetInstance()->ToggleHearBeatLed();
}