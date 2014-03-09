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

        Timer2( void );
        
        void Vector9( void );
        
        void Vector10( void );
        
        public:
        
        static Timer2* GetInstance( void );
        
        void Configure(Timer2WaveFormGenerationMode::ETimer2WaveFormGenerationMode waveFormGenerationMode, Timer2CompareOutputMode::ETimer2CompareOutputMode compareOutputMode, Timer2Prescaller::ETimer2Prescaller prescaller);
        
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
        
        friend void __vector_9( void );
        
        friend void __vector_10( void );
    };
};

#endif