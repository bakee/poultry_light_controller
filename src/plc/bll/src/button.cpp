#include "../inc/button.h"
#include "../inc/task_dispatcher.h"

namespace bll
{
    using namespace hal;
    
    Button* Button::_instance = NULL;

    Button::Button()
    {
        _menu = Menu::GetInstance();
        _configuration = Configuration::GetInstance();
        
        _isPlusButtonPressed = false;
        _isMinusButtonPressed = false;
        _numberOfSecondsPassed = 0;
        
        // Configure buttons
        _pinInterrupt = PinInterrupt::GetInstance();
        
        _pinInterrupt->SetInterrupt4Handler(FriendOnModeButtonPressed);
        _pinInterrupt->SetInterrupt4Mode(InterruptSenseControl::InterruptOnFallingEdge);
        _pinInterrupt->EnableInterrupt4();
        _pinInterrupt->ClearInterrupt4Flag();
        
        _pinInterrupt->SetInterrupt5Handler(FriendOnPlusButtonPressed);
        _pinInterrupt->SetInterrupt5ReleasedHandler(FriendOnPlusButtonReleased);
        _pinInterrupt->SetInterrupt5Mode(InterruptSenseControl::InterruptOnBothEdge);
        _pinInterrupt->EnableInterrupt5();
        _pinInterrupt->ClearInterrupt5Flag();
        
        _pinInterrupt->SetInterrupt6Handler(FriendOnMinusButtonPressed);
        _pinInterrupt->SetInterrupt6ReleasedHandler(FriendOnMinusButtonReleased);
        _pinInterrupt->SetInterrupt6Mode(InterruptSenseControl::InterruptOnBothEdge);
        _pinInterrupt->EnableInterrupt6();
        _pinInterrupt->ClearInterrupt6Flag();
        
        _pinInterrupt->SetInterrupt7Handler(FriendOnBackButtonPressed);
        _pinInterrupt->SetInterrupt7Mode(InterruptSenseControl::InterruptOnFallingEdge);
        _pinInterrupt->EnableInterrupt7();
        _pinInterrupt->ClearInterrupt7Flag();
        
        TaskDispatcher::GetInstance()->AddTask(FriendOnButtonLongPressed);
    }

    Button* Button::GetInstance()
    {
        if (_instance == NULL)
        {
            static Button object;
            _instance = &object;
        }
        
        return _instance;
    }

    void Button::OnModeButtonPressed( void )
    {
        _configuration->SetNextEventHandler();
    }

    void Button::OnPlusButtonPressed( void )
    {
        if(_isMinusButtonPressed)
        {
            return;
        }
        
        _isPlusButtonPressed = true;
        _numberOfSecondsPassed = 0;
        _configuration->IncreaseValue(IncreaseDecreaseType::Normal);
    }
    
    void Button::OnPlusButtonReleased( void )
    {
        _isPlusButtonPressed = false;
        _numberOfSecondsPassed = 0;
    }

    void Button::OnMinusButtonPressed( void )
    {
        if(_isPlusButtonPressed)
        {
            return;
        }
        
        _isMinusButtonPressed = true;
        _numberOfSecondsPassed = 0;
        _configuration->DecreaseValue(IncreaseDecreaseType::Normal);
    }
    
    void Button::OnMinusButtonReleased( void )
    {
        _isMinusButtonPressed = false;
        _numberOfSecondsPassed = 0;
    }

    void Button::OnBackButtonPressed( void )
    {
        _configuration->SetPreviousEventHandler();
    }

    IncreaseDecreaseType::EIncreaseDecreaseType Button::GetLongPressMode(){

    	IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType = IncreaseDecreaseType::None;

        if(_numberOfSecondsPassed <= TaskDispatcher::GetInterruptRate() * 2) // For the first 2 second do nothing
        {
            _numberOfSecondsPassed++;
        }
        else if (_numberOfSecondsPassed <= TaskDispatcher::GetInterruptRate() * 7) // For the next 5 seconds, increase normally
        {
            _numberOfSecondsPassed++;
            increaseDecreaseType = IncreaseDecreaseType::Normal;
        }
        else if (_numberOfSecondsPassed <= TaskDispatcher::GetInterruptRate() * 12) // For the next 5 seconds, increase fast
        {
            _numberOfSecondsPassed++;
            increaseDecreaseType = IncreaseDecreaseType::Fast;
        }
        else // For the next seconds, increase faster
        {
        	increaseDecreaseType = IncreaseDecreaseType::Faster;
        }

        return increaseDecreaseType;
    }

    void Button::OnButtonLongPressed( void )
    {
    	 IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType = GetLongPressMode();

    	 if(increaseDecreaseType == IncreaseDecreaseType::None){
    		 return;
    	 }

        if(_isPlusButtonPressed) // TODO: need to add another condition to detect whether the button is still being pressed or not
        {
        	_configuration->IncreaseValue(increaseDecreaseType);
        }
        else if(_isMinusButtonPressed) // TODO: need to add another condition to detect whether the button is still being pressed or not
        {
        	_configuration->DecreaseValue(increaseDecreaseType);
        }
    }

    void FriendOnModeButtonPressed()
    {
        Button::_instance->OnModeButtonPressed();
    }

    void FriendOnPlusButtonPressed( void )
    {
        Button::_instance->OnPlusButtonPressed();
    }
    
    void FriendOnPlusButtonReleased( void )
    {
        Button::_instance->OnPlusButtonReleased();
    }

    void FriendOnMinusButtonPressed( void )
    {
        Button::_instance->OnMinusButtonPressed();
    }
    
    void FriendOnMinusButtonReleased( void )
    {
        Button::_instance->OnMinusButtonReleased();
    }

    void FriendOnBackButtonPressed( void )
    {
        Button::_instance->OnBackButtonPressed();
    }

    void FriendOnButtonLongPressed( void )
    {
        Button::_instance->OnButtonLongPressed();
    }

};
