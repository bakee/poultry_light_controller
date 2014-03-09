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

        Timer0( void );
        
        void Vector15( void );
        
        void Vector16( void );
        
        public:
        
        static Timer0* GetInstance( void );
        
        void Configure(Timer0WaveFormGenerationMode::ETimer0WaveFormGenerationMode waveFormGenerationMode, Timer0CompareOutputMode::ETimer0CompareOutputMode compareOutputMode, Timer0Prescaller::ETimer0Prescaller prescaller, bool isAsynchronousMode);
        
        void SetValue(unsigned char value);
        
        unsigned char GetValue( void );
        
        void SetCompareRegister(unsigned char value);
        
        unsigned char GetCompareRegister( void );
        
        void EnableOverflowInterrupt( void );
        
        void DisableOverflowInterrupt( void );
        
        void EnableCompareMatchInterrupt( void );
        
        void DisableCompareMatchInterrupt( void );
        
        void SetOverflowInterruptHandler(InterruptHandler handler);
        
        void SetCompareMatchInterruptHandler(InterruptHandler handler);
        
        friend void __vector_15( void );
        
        friend void __vector_16( void );
    };
};

#endif