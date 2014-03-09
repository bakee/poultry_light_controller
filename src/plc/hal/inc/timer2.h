/*
* timer2.h
*
* Created: 1/13/2013 5:14:40 PM
*  Author: muhammad
*/


#ifndef TIMER2_H_
#define TIMER2_H_

#include "hal_utils.h"

namespace hal
{
    class Timer2WaveFormGenerationMode
    {
        public:
        typedef enum
        {
            Normal,
            PhaseCorrectPwm,
            Ctc,
            FastPwm
        } ETimer2WaveFormGenerationMode;
    };
    
    class Timer2CompareOutputMode
    {
        public:
        typedef enum
        {
            NormalPortOperation,
            ToggleOc0OnCompareMatch,
            ClearOc0OnCompareMatch,
            SetOc0OnCompareMatch
        } ETimer2CompareOutputMode;
    };

    class Timer2CompareOutputMode_NonPwmMode
    {
        public:
        typedef enum
        {
            NormalPortOperation,
            ToggleOc0OnCompareMatch,
            ClearOc0OnCompareMatch,
            SetOc0OnCompareMatch
        } ETimer2CompareOutputMode_NonPwmMode;
    };
    
    class Timer2CompareOutputMode_FastPwmMode
    {
        public:
        typedef enum
        {
            NormalPortOperation,
            Reserved,
            ClearOc0OnCompareMatch,
            SetOc0OnCompareMatch
        } ETimer2CompareOutputMode_FastPwmMode;
    };
    
    class Timer2CompareOutputMode_PhaseCorrectPwmMode
    {
        public:
        typedef enum
        {
            NormalPortOperation,
            Reserved,
            ClearOc0OnCompareMatchWhenUpCounting,
            SetOc0OnCompareMatchWhenUpCounting
        } ETimer2CompareOutputMode_PhaseCorrectPwmMode;
    };
    
    class Timer2Prescaller
    {
        public:
        typedef enum
        {
            NoClockSource,
            DividedBy1,
            DividedBy8,
            DividedBy64,
            DividedBy256,
            DividedBy1024,
            ExternalCloclSourceOnT2OnFallingEdge,
            ExternalClockSourceOnT2OnRisingEdge
        } ETimer2Prescaller;
    };
    
    class Timer2
    {
        private:
        
        static Timer2* _instance;
        
        InterruptHandler _overflowInterruptHandler;
        
        InterruptHandler _compareMatchInterruptHandler;
        
        //************************************
        // Method:    Timer2
        // FullName:  hal::Timer2::Timer2
        // Access:    private
        // Returns:
        // Qualifier:
        // Parameter: void
        //************************************
        Timer2( void );
        
        //************************************
        // Method:    Vector9
        // FullName:  hal::Timer2::Vector9
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Vector9( void );
        
        //************************************
        // Method:    Vector10
        // FullName:  hal::Timer2::Vector10
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Vector10( void );
        
        public:
        
        //************************************
        // Method:    GetInstance
        // FullName:  hal::Timer2::GetInstance
        // Access:    public static
        // Returns:   Timer2*
        // Qualifier:
        // Parameter: void
        //************************************
        static Timer2* GetInstance( void );
        
        //************************************
        // Method:    Configure
        // FullName:  hal::Timer2::Configure
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: Timer2WaveFormGenerationMode::ETimer2WaveFormGenerationMode waveFormGenerationMode
        // Parameter: Timer2CompareOutputMode::ETimer2CompareOutputMode compareOutputMode
        // Parameter: Timer2Prescaller::ETimer2Prescaller prescaller
        //************************************
        void Configure(Timer2WaveFormGenerationMode::ETimer2WaveFormGenerationMode waveFormGenerationMode, Timer2CompareOutputMode::ETimer2CompareOutputMode compareOutputMode, Timer2Prescaller::ETimer2Prescaller prescaller);
        
        //************************************
        // Method:    SetValue
        // FullName:  hal::Timer2::SetValue
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char value
        //************************************
        void SetValue(unsigned char value);
        
        //************************************
        // Method:    GetValue
        // FullName:  hal::Timer2::GetValue
        // Access:    public
        // Returns:   unsigned char
        // Qualifier:
        // Parameter: void
        //************************************
        unsigned char GetValue( void );
        
        //************************************
        // Method:    SetCompareRegister
        // FullName:  hal::Timer2::SetCompareRegister
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char value
        //************************************
        void SetCompareRegister(unsigned char value);
        
        //************************************
        // Method:    GetCompareRegister
        // FullName:  hal::Timer2::GetCompareRegister
        // Access:    public
        // Returns:   unsigned char
        // Qualifier:
        // Parameter: void
        //************************************
        unsigned char GetCompareRegister( void );
        
        //************************************
        // Method:    EnableOverflowInterrupt
        // FullName:  hal::Timer2::EnableOverflowInterrupt
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void EnableOverflowInterrupt( void );
        
        //************************************
        // Method:    DisableOverflowInterrupt
        // FullName:  hal::Timer2::DisableOverflowInterrupt
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void DisableOverflowInterrupt( void );
        
        //************************************
        // Method:    EnableCompareMatchInterrupt
        // FullName:  hal::Timer2::EnableCompareMatchInterrupt
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void EnableCompareMatchInterrupt( void );
        
        //************************************
        // Method:    DisableCompareMatchInterrupt
        // FullName:  hal::Timer2::DisableCompareMatchInterrupt
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void DisableCompareMatchInterrupt( void );
        
        //************************************
        // Method:    SetOverflowInterruptHandler
        // FullName:  hal::Timer2::SetOverflowInterruptHandler
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptHandler handler
        //************************************
        void SetOverflowInterruptHandler(InterruptHandler handler);
        
        //************************************
        // Method:    SetCompareMatchInterruptHandler
        // FullName:  hal::Timer2::SetCompareMatchInterruptHandler
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptHandler handler
        //************************************
        void SetCompareMatchInterruptHandler(InterruptHandler handler);
        
        //************************************
        // Method:    __vector_9
        // FullName:  hal::__vector_9
        // Access:    public
        // Returns:   friend void
        // Qualifier:
        // Parameter: void
        //************************************
        friend void __vector_9( void );
        
        //************************************
        // Method:    __vector_10
        // FullName:  hal::__vector_10
        // Access:    public
        // Returns:   friend void
        // Qualifier:
        // Parameter: void
        //************************************
        friend void __vector_10( void );
    };
};



#endif /* TIMER2_H_ */