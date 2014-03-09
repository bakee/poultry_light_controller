/*
* timer0.cpp
*
* Created: 1/13/2013 12:35:24 PM
*  Author: muhammad
*/
#include "../inc/timer0.h"
#include <avr/io.h>

namespace hal
{
    Timer0* Timer0::_instance = NULL;

    //************************************
    // Method:    Timer0
    // FullName:  hal::Timer0::Timer0
    // Access:    public
    // Returns:
    // Qualifier:
    //************************************
    Timer0::Timer0()
    {
        _compareMatchInterruptHandler = NULL;
        _overflowInterruptHandler = NULL;
    }
    
    //************************************
    // Method:    GetInstance
    // FullName:  hal::Timer0::GetInstance
    // Access:    public static
    // Returns:   Timer0*
    // Qualifier:
    //************************************
    Timer0* Timer0::GetInstance()
    {
        if (_instance == NULL)
        {
            static Timer0 object;
            _instance = &object;
        }
        
        return _instance;
    }

    //************************************
    // Method:    Configure
    // FullName:  hal::Timer0::Configure
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: Timer0WaveFormGenerationMode waveFormGenerationMode
    // Parameter: Timer0CompareOutputMode compareOutputMode
    // Parameter: Timer0Prescaller prescaller
    // Parameter: bool isAsynchronousMode
    //************************************
    void Timer0::Configure(Timer0WaveFormGenerationMode::ETimer0WaveFormGenerationMode waveFormGenerationMode, Timer0CompareOutputMode::ETimer0CompareOutputMode compareOutputMode, Timer0Prescaller::ETimer0Prescaller prescaller, bool isAsynchronousMode)
    {
        unsigned char tccr0 = 0;
        
        switch(waveFormGenerationMode)
        {
            case Timer0WaveFormGenerationMode::PhaseCorrectPwm:
            tccr0 |= (1 << WGM00);
            break;
            case Timer0WaveFormGenerationMode::Ctc:
            tccr0 |= (1 << WGM01);
            break;
            case Timer0WaveFormGenerationMode::FastPwm:
            tccr0 |= ((1 << WGM01) | (1 << WGM00));
            break;
            case Timer0WaveFormGenerationMode::Normal:
            default:
            break;
        }
        
        switch(compareOutputMode)
        {
            case Timer0CompareOutputMode::ToggleOc0OnCompareMatch:
            tccr0 |= (1 << COM00);
            break;
            case Timer0CompareOutputMode::ClearOc0OnCompareMatch:
            tccr0 |= (1 << COM01);
            break;
            case Timer0CompareOutputMode::SetOc0OnCompareMatch:
            tccr0 |= ((1 << COM01) | (1 << COM00));
            break;
            case Timer0CompareOutputMode::NormalPortOperation:
            default:
            break;
        }
        
        switch(prescaller)
        {
            case Timer0Prescaller::DividedBy1:
            tccr0 |= (1 << CS00);
            break;
            case Timer0Prescaller::DividedBy8:
            tccr0 |= (1 << CS01);
            break;
            case Timer0Prescaller::DividedBy32:
            tccr0 |= ((1 << CS01) | (1 << CS00));
            break;
            case Timer0Prescaller::DividedBy64:
            tccr0 |= (1 << CS02);
            break;
            case Timer0Prescaller::DividedBy128:
            tccr0 |= ((1 << CS02) | (1 << CS00));
            break;
            case Timer0Prescaller::DividedBy256:
            tccr0 |= ((1 << CS02) | (1 << CS01));
            break;
            case Timer0Prescaller::DividedBy1024:
            tccr0 |= ((1 << CS02) | (1 << CS01) | (1 << CS00));
            break;
            case Timer0Prescaller::NoClockSource:
            default:
            break;
        }
        
        TCCR0 = tccr0;
        
        if (isAsynchronousMode)
        {
            ASSR |= (1 << AS0);
        }
    }

    //************************************
    // Method:    SetValue
    // FullName:  hal::Timer0::SetValue
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: unsigned char value
    //************************************
    void Timer0::SetValue(unsigned char value)
    {
        TCNT0 = value;
    }

    //************************************
    // Method:    GetValue
    // FullName:  hal::Timer0::GetValue
    // Access:    public
    // Returns:   unsigned char
    // Qualifier:
    // Parameter: void
    //************************************
    unsigned char Timer0::GetValue( void )
    {
        return TCNT0;
    }

    //************************************
    // Method:    SetCompareRegister
    // FullName:  hal::Timer0::SetCompareRegister
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: unsigned char value
    //************************************
    void Timer0::SetCompareRegister(unsigned char value)
    {
        OCR0 = value;
    }

    //************************************
    // Method:    GetCompareRegister
    // FullName:  hal::Timer0::GetCompareRegister
    // Access:    public
    // Returns:   unsigned char
    // Qualifier:
    //************************************
    unsigned char Timer0::GetCompareRegister()
    {
        return OCR0;
    }

    //************************************
    // Method:    EnableOverflowInterrupt
    // FullName:  hal::Timer0::EnableOverflowInterrupt
    // Access:    public
    // Returns:   void
    // Qualifier:
    //************************************
    void Timer0::EnableOverflowInterrupt()
    {
        TIMSK |= (1 << TOIE0);
    }

    //************************************
    // Method:    DisableOverflowInterrupt
    // FullName:  hal::Timer0::DisableOverflowInterrupt
    // Access:    public
    // Returns:   void
    // Qualifier:
    //************************************
    void Timer0::DisableOverflowInterrupt()
    {
        TIMSK &= ~(1 << TOIE0);
    }

    //************************************
    // Method:    EnableCompareMatchInterrupt
    // FullName:  hal::Timer0::EnableCompareMatchInterrupt
    // Access:    public
    // Returns:   void
    // Qualifier:
    //************************************
    void Timer0::EnableCompareMatchInterrupt()
    {
        TIMSK |= (1 << OCIE0);
    }
    
    //************************************
    // Method:    DisableCompareMatchInterrupt
    // FullName:  hal::Timer0::DisableCompareMatchInterrupt
    // Access:    public
    // Returns:   void
    // Qualifier:
    //************************************
    void Timer0::DisableCompareMatchInterrupt()
    {
        TIMSK &= ~(1 << OCIE0);
    }

    //************************************
    // Method:    SetOverflowInterruptHandler
    // FullName:  hal::Timer0::SetOverflowInterruptHandler
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptHandler handler
    //************************************
    void Timer0::SetOverflowInterruptHandler(InterruptHandler handler)
    {
        _overflowInterruptHandler = handler;
    }

    //************************************
    // Method:    SetCompareMatchInterruptHandler
    // FullName:  hal::Timer0::SetCompareMatchInterruptHandler
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptHandler handler
    //************************************
    void Timer0::SetCompareMatchInterruptHandler(InterruptHandler handler)
    {
        _compareMatchInterruptHandler = handler;
    }

    //************************************
    // Method:    Vector15
    // FullName:  hal::Timer0::Vector15
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Timer0::Vector15( void )
    {
        if (_compareMatchInterruptHandler != NULL)
        {
            _compareMatchInterruptHandler();
        }
    }

    //************************************
    // Method:    Vector16
    // FullName:  hal::Timer0::Vector16
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Timer0::Vector16( void )
    {
        if(_overflowInterruptHandler != NULL)
        {
            _overflowInterruptHandler();
        }
    }

    //************************************
    // Method:    __vector_15
    // FullName:  hal::__vector_15
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void __vector_15( void )
    {
        Timer0::_instance->Vector15();
    }

    //************************************
    // Method:    __vector_16
    // FullName:  hal::__vector_16
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void __vector_16( void )
    {
        Timer0::_instance->Vector16();
    }
};