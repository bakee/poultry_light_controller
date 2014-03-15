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

        volatile unsigned int _numberOfSecondsPassed;
                    
        Button( void );        

        void OnModeButtonPressed( void ); 
       
        void OnPlusButtonPressed( void );

        void OnPlusButtonReleased( void );  
      
        void OnMinusButtonPressed( void );

        void OnMinusButtonReleased( void ); 
               
        void OnBackButtonPressed( void );  
      
        void OnButtonLongPressed( void );
        
        IncreaseDecreaseType::EIncreaseDecreaseType GetLongPressMode( void );

        public:        

        static Button* GetInstance( void );  
              
        friend void FriendOnModeButtonPressed( void ); 
      
        friend void FriendOnPlusButtonPressed( void );

        friend void FriendOnPlusButtonReleased( void );

        friend void FriendOnMinusButtonPressed( void );

        friend void FriendOnMinusButtonReleased( void ); 
     
        friend void FriendOnBackButtonPressed( void );   
     
        friend void FriendOnButtonLongPressed( void );
    };
};

#endif
