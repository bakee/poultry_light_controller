/*
* timer0.h
*
* Created: 1/13/2013 10:44:57 AM
*  Author: muhammad
*/

#ifndef TIMER0_H_
#define TIMER0_H_

#include "hal_utils.h"

namespace hal
{
    class Timer0WaveFormGenerationMode
    {
        public:
        typedef enum
        {
            Normal,
            PhaseCorrectPwm,
            Ctc,
            FastPwm
        } ETimer0WaveFormGenerationMode;
    };
    
    class Timer0CompareOutputMode
    {
        public:
        typedef enum
        {
            NormalPortOperation,
            ToggleOc0OnCompareMatch,
            ClearOc0OnCompareMatch,
            SetOc0OnCompareMatch
        } ETimer0CompareOutputMode;
    };

    class Timer0CompareOutputMode_NonPwmMode
    {
        public:
        typedef enum
        {
            NormalPortOperation,
            ToggleOc0OnCompareMatch,
            ClearOc0OnCompareMatch,
            SetOc0OnCompareMatch
        } ETimer0CompareOutputMode_NonPwmMode;
    };
    
    class Timer0CompareOutputMode_FastPwmMode
    {
        public:
        typedef enum
        {
            NormalPortOperation,
            Reserved,
            ClearOc0OnCompareMatch,
            SetOc0OnCompareMatch
        } ETimer0CompareOutputMode_FastPwmMode;
    };
    
    class Timer0CompareOutputMode_PhaseCorrectPwmMode
    {
        public:
        typedef enum
        {
            NormalPortOperation,
            Reserved,
            ClearOc0OnCompareMatchWhenUpCounting,
            SetOc0OnCompareMatchWhenUpCounting
        } ETimer0CompareOutputMode_PhaseCorrectPwmMode;
    };
    
    class Timer0Prescaller
    {
        public:
        typedef enum
        {
            NoClockSource,
            DividedBy1,
            DividedBy8,
            DividedBy32,
            DividedBy64,
            DividedBy128,
            DividedBy256,
            DividedBy1024
        } ETimer0Prescaller;
    };
    
    class Timer0
    {
        private:
        
        static Timer0* _instance;
        
        InterruptHandler _overflowInterruptHandler;
        
        InterruptHandler _compareMatchInterruptHandler;
        
        //************************************
        // Method:    Timer0
        // FullName:  hal::Timer0::Timer0
        // Access:    private
        // Returns:
        // Qualifier:
        // Parameter: void
        //************************************
        Timer0( void );
        
        //************************************
        // Method:    Vector15
        // FullName:  hal::Timer0::Vector15
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Vector15( void );
        
        //************************************
        // Method:    Vector16
        // FullName:  hal::Timer0::Vector16
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Vector16( void );
        
        public:
        
        //************************************
        // Method:    GetInstance
        // FullName:  hal::Timer0::GetInstance
        // Access:    public static
        // Returns:   Timer0*
        // Qualifier:
        // Parameter: void
        //************************************
        static Timer0* GetInstance( void );
        
        //************************************
        // Method:    Configure
        // FullName:  hal::Timer0::Configure
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: Timer0WaveFormGenerationMode::ETimer0WaveFormGenerationMode waveFormGenerationMode
        // Parameter: Timer0CompareOutputMode::ETimer0CompareOutputMode compareOutputMode
        // Parameter: Timer0Prescaller::ETimer0Prescaller prescaller
        // Parameter: bool isAsynchronousMode
        //************************************
        void Configure(Timer0WaveFormGenerationMode::ETimer0WaveFormGenerationMode waveFormGenerationMode, Timer0CompareOutputMode::ETimer0CompareOutputMode compareOutputMode, Timer0Prescaller::ETimer0Prescaller prescaller, bool isAsynchronousMode);
        
        //************************************
        // Method:    SetValue
        // FullName:  hal::Timer0::SetValue
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char value
        //************************************
        void SetValue(unsigned char value);
        
        //************************************
        // Method:    GetValue
        // FullName:  hal::Timer0::GetValue
        // Access:    public
        // Returns:   unsigned char
        // Qualifier:
        // Parameter: void
        //************************************
        unsigned char GetValue( void );
        
        //************************************
        // Method:    SetCompareRegister
        // FullName:  hal::Timer0::SetCompareRegister
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char value
        //************************************
        void SetCompareRegister(unsigned char value);
        
        //************************************
        // Method:    GetCompareRegister
        // FullName:  hal::Timer0::GetCompareRegister
        // Access:    public
        // Returns:   unsigned char
        // Qualifier:
        // Parameter: void
        //************************************
        unsigned char GetCompareRegister( void );
        
        //************************************
        // Method:    EnableOverflowInterrupt
        // FullName:  hal::Timer0::EnableOverflowInterrupt
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void EnableOverflowInterrupt( void );
        
        //************************************
        // Method:    DisableOverflowInterrupt
        // FullName:  hal::Timer0::DisableOverflowInterrupt
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void DisableOverflowInterrupt( void );
        
        //************************************
        // Method:    EnableCompareMatchInterrupt
        // FullName:  hal::Timer0::EnableCompareMatchInterrupt
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void EnableCompareMatchInterrupt( void );
        
        //************************************
        // Method:    DisableCompareMatchInterrupt
        // FullName:  hal::Timer0::DisableCompareMatchInterrupt
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void DisableCompareMatchInterrupt( void );
        
        //************************************
        // Method:    SetOverflowInterruptHandler
        // FullName:  hal::Timer0::SetOverflowInterruptHandler
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptHandler handler
        //************************************
        void SetOverflowInterruptHandler(InterruptHandler handler);
        
        //************************************
        // Method:    SetCompareMatchInterruptHandler
        // FullName:  hal::Timer0::SetCompareMatchInterruptHandler
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptHandler handler
        //************************************
        void SetCompareMatchInterruptHandler(InterruptHandler handler);
        
        //************************************
        // Method:    __vector_15
        // FullName:  hal::__vector_15
        // Access:    public
        // Returns:   friend void
        // Qualifier:
        // Parameter: void
        //************************************
        friend void __vector_15( void );
        
        //************************************
        // Method:    __vector_16
        // FullName:  hal::__vector_16
        // Access:    public
        // Returns:   friend void
        // Qualifier:
        // Parameter: void
        //************************************
        friend void __vector_16( void );
    };
};

#endif /* TIMER0_H_ */