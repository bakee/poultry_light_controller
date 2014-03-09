/*
* button.h
*
* Created: 1/20/2013 3:31:02 PM
*  Author: muhammad
*/


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../hal/inc/pin_interrupt.h"
#include "../inc/menu.h"
#include "../inc/configuration.h"

namespace bll
{
    void FriendOnModeButtonPressed( void );
    void FriendOnPlusButtonPressed( void );
    void FriendOnPlusButtonReleased( void );
    void FriendOnMinusButtonPressed( void );
    void FriendOnMinusButtonReleased( void );
    void FriendOnBackButtonPressed( void );
    
    void FriendOnButtonLongPressed( void );
    
    class Buttons
    {
        typedef enum
        {
            ModeButton,
            PlusButton,
            MinusButton,
            BackButton
        } EButtons;
    };
    
    class Button
    {
        private:
        
        static Button* _instance;
        
        hal::PinInterrupt* _pinInterrupt;
        
        Menu* _menu;
        
        Configuration* _configuration;
        
        volatile bool _isPlusButtonPressed;
        volatile bool _isMinusButtonPressed;
        volatile unsigned char _numberOfSecondsPassed;               
        
        //************************************
        // Method:    Button
        // FullName:  bll::Button::Button
        // Access:    private
        // Returns:
        // Qualifier:
        // Parameter: void
        //************************************
        Button( void );
        
        //************************************
        // Method:    OnModeButtonPressed
        // FullName:  bll::Button::OnModeButtonPressed
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void OnModeButtonPressed( void );
        
        //************************************
        // Method:    OnPlusButtonPressed
        // FullName:  bll::Button::OnPlusButtonPressed
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void OnPlusButtonPressed( void );
        void OnPlusButtonReleased( void );
        
        //************************************
        // Method:    OnMinusButtonPressed
        // FullName:  bll::Button::OnMinusButtonPressed
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void OnMinusButtonPressed( void );
        void OnMinusButtonReleased( void );        
        
        //************************************
        // Method:    OnBackButtonPressed
        // FullName:  bll::Button::OnBackButtonPressed
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void OnBackButtonPressed( void );
        
        void OnButtonLongPressed( void );
        
        public:
        
        //************************************
        // Method:    GetInstance
        // FullName:  bll::Button::GetInstance
        // Access:    public static
        // Returns:   Button*
        // Qualifier:
        // Parameter: void
        //************************************
        static Button* GetInstance( void );        
        
        //************************************
        // Method:    FriendOnModeButtonPressed
        // FullName:  bll::FriendOnModeButtonPressed
        // Access:    public
        // Returns:   friend void
        // Qualifier:
        // Parameter: void
        //************************************
        friend void FriendOnModeButtonPressed( void );
        
        //************************************
        // Method:    FriendOnPlusButtonPressed
        // FullName:  bll::FriendOnPlusButtonPressed
        // Access:    public
        // Returns:   friend void
        // Qualifier:
        // Parameter: void
        //************************************
        friend void FriendOnPlusButtonPressed( void );
        friend void FriendOnPlusButtonReleased( void );
        
        //************************************
        // Method:    FriendOnMinusButtonPressed
        // FullName:  bll::FriendOnMinusButtonPressed
        // Access:    public
        // Returns:   friend void
        // Qualifier:
        // Parameter: void
        //************************************
        friend void FriendOnMinusButtonPressed( void );
        friend void FriendOnMinusButtonReleased( void );
        
        //************************************
        // Method:    FriendOnBackButtonPressed
        // FullName:  bll::FriendOnBackButtonPressed
        // Access:    public
        // Returns:   friend void
        // Qualifier:
        // Parameter: void
        //************************************
        friend void FriendOnBackButtonPressed( void );
        
        friend void FriendOnButtonLongPressed( void );
    };
};


#endif /* BUTTON_H_ */