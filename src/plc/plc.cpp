/*
* incubator.cpp
*
* Created: 1/2/2013 9:10:37 PM
*  Author: muhammad
*/

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "hal/inc/led.h"
#include "hal/inc/lcd.h"
#include "hal/inc/timer0.h"

#include "bll/inc/sensor.h"
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
    Sensor* sensor = Sensor::GetInstance();
    Display* display = Display::GetInstance();

    sei();
    
    while(1)
    {
        int currentTemperature = sensor->GetTemperature();
        int currentHumidity = sensor->GetHumidity();
        int timer2RemainingTime = relayManager->GetTimer2RemainingTime();
        
        if(relayManager->GetApplicationState())
        {
            display->Show(currentTemperature, DisplayName::Temperature);
            display->Show(currentHumidity, DisplayName::Humidity);
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