#include "../inc/timer0.h"
#include <avr/io.h>

namespace hal
{
    Timer0* Timer0::_instance = NULL;

    Timer0::Timer0()
    {
        _compareMatchInterruptHandler = NULL;
        _overflowInterruptHandler = NULL;
    }
    
    Timer0* Timer0::GetInstance()
    {
        if (_instance == NULL)
        {
            static Timer0 object;
            _instance = &object;
        }
        
        return _instance;
    }

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

    void Timer0::SetValue(unsigned char value)
    {
        TCNT0 = value;
    }

    unsigned char Timer0::GetValue( void )
    {
        return TCNT0;
    }

    void Timer0::SetCompareRegister(unsigned char value)
    {
        OCR0 = value;
    }

    unsigned char Timer0::GetCompareRegister()
    {
        return OCR0;
    }

    void Timer0::EnableOverflowInterrupt()
    {
        TIMSK |= (1 << TOIE0);
    }

    void Timer0::DisableOverflowInterrupt()
    {
        TIMSK &= ~(1 << TOIE0);
    }

    void Timer0::EnableCompareMatchInterrupt()
    {
        TIMSK |= (1 << OCIE0);
    }
    
    void Timer0::DisableCompareMatchInterrupt()
    {
        TIMSK &= ~(1 << OCIE0);
    }

    void Timer0::SetOverflowInterruptHandler(InterruptHandler handler)
    {
        _overflowInterruptHandler = handler;
    }

    void Timer0::SetCompareMatchInterruptHandler(InterruptHandler handler)
    {
        _compareMatchInterruptHandler = handler;
    }

    void Timer0::Vector15( void )
    {
        if (_compareMatchInterruptHandler != NULL)
        {
            _compareMatchInterruptHandler();
        }
    }

    void Timer0::Vector16( void )
    {
        if(_overflowInterruptHandler != NULL)
        {
            _overflowInterruptHandler();
        }
    }

    void __vector_15( void )
    {
        Timer0::_instance->Vector15();
    }

    void __vector_16( void )
    {
        Timer0::_instance->Vector16();
    }
};