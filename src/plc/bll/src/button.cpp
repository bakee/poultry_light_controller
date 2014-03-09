/*
* button.cpp
*
* Created: 1/20/2013 3:31:12 PM
*  Author: muhammad
*/

#include "../inc/button.h"
#include "../inc/task_dispatcher.h"

namespace bll
{
    using namespace hal;
    
    Button* Button::_instance = NULL;

    //************************************
    // Method:    Button
    // FullName:  bll::Button::Button
    // Access:    private
    // Returns:
    // Qualifier:
    //************************************
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

    //************************************
    // Method:    GetInstance
    // FullName:  bll::Button::GetInstance
    // Access:    public static
    // Returns:   Button*
    // Qualifier:
    //************************************
    Button* Button::GetInstance()
    {
        if (_instance == NULL)
        {
            static Button object;
            _instance = &object;
        }
        
        return _instance;
    }

    //************************************
    // Method:    OnModeButtonPressed
    // FullName:  bll::Button::OnModeButtonPressed
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Button::OnModeButtonPressed( void )
    {
        _configuration->SetNextEventHandler();
    }

    //************************************
    // Method:    OnPlusButtonPressed
    // FullName:  bll::Button::OnPlusButtonPressed
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
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
    }

    //************************************
    // Method:    OnMinusButtonPressed
    // FullName:  bll::Button::OnMinusButtonPressed
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
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
    }

    //************************************
    // Method:    OnBackButtonPressed
    // FullName:  bll::Button::OnBackButtonPressed
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Button::OnBackButtonPressed( void )
    {
        _configuration->SetPreviousEventHandler();
    }

    void Button::OnButtonLongPressed( void )
    {
        if(_isPlusButtonPressed) // TODO: need to add another condition to detect whether the button is still being pressed or not
        {
            if(TaskDispatcher::GetInterruptRate() > _numberOfSecondsPassed)
            {
                _numberOfSecondsPassed++;
            }
            else if (TaskDispatcher::GetInterruptRate() * 5 >= _numberOfSecondsPassed)
            {
                _numberOfSecondsPassed++;
                _configuration->IncreaseValue(IncreaseDecreaseType::Normal);
            }
            else if ( TaskDispatcher::GetInterruptRate() * 10 >= _numberOfSecondsPassed)
            {
                _numberOfSecondsPassed++;
                _configuration->IncreaseValue(IncreaseDecreaseType::Fast);
            }
            else
            {
                _configuration->IncreaseValue(IncreaseDecreaseType::Faster);
            }
        }
        else if(_isMinusButtonPressed) // TODO: need to add another condition to detect whether the button is still being pressed or not
        {
            if(TaskDispatcher::GetInterruptRate() > _numberOfSecondsPassed)
            {
                _numberOfSecondsPassed++;
            }
            else if (TaskDispatcher::GetInterruptRate() * 5 >= _numberOfSecondsPassed)
            {
                _numberOfSecondsPassed++;
                _configuration->DecreaseValue(IncreaseDecreaseType::Normal);
            }
            else if (TaskDispatcher::GetInterruptRate() * 10 >= _numberOfSecondsPassed)
            {
                _numberOfSecondsPassed++;
                _configuration->DecreaseValue(IncreaseDecreaseType::Fast);
            }
            else
            {
                _configuration->DecreaseValue(IncreaseDecreaseType::Faster);
            }
        }
    }

    //************************************
    // Method:    FriendOnModeButtonPressed
    // FullName:  bll::FriendOnModeButtonPressed
    // Access:    public
    // Returns:   void
    // Qualifier:
    //************************************
    void FriendOnModeButtonPressed()
    {
        Button::_instance->OnModeButtonPressed();
    }

    //************************************
    // Method:    FriendOnPlusButtonPressed
    // FullName:  bll::FriendOnPlusButtonPressed
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void FriendOnPlusButtonPressed( void )
    {
        Button::_instance->OnPlusButtonPressed();
    }
    
    void FriendOnPlusButtonReleased( void )
    {
        Button::_instance->OnPlusButtonReleased();
    }

    //************************************
    // Method:    FriendOnMinusButtonPressed
    // FullName:  bll::FriendOnMinusButtonPressed
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void FriendOnMinusButtonPressed( void )
    {
        Button::_instance->OnMinusButtonPressed();
    }
    
    void FriendOnMinusButtonReleased( void )
    {
        Button::_instance->OnMinusButtonReleased();
    }

    //************************************
    // Method:    FriendOnBackButtonPressed
    // FullName:  bll::FriendOnBackButtonPressed
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void FriendOnBackButtonPressed( void )
    {
        Button::_instance->OnBackButtonPressed();
    }

    void FriendOnButtonLongPressed( void )
    {
        Button::_instance->OnButtonLongPressed();
    }

};