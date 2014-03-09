#include "../inc/timer2.h"
#include <avr/io.h>

namespace hal
{
    Timer2* Timer2::_instance = NULL;

    Timer2::Timer2()
    {
        _compareMatchInterruptHandler = NULL;
        _overflowInterruptHandler = NULL;
    }
    
    Timer2* Timer2::GetInstance()
    {
        if(_instance == NULL)
        {
            static Timer2 object;
            _instance = &object;
        }
        
        return _instance;
    }

    void Timer2::Configure(Timer2WaveFormGenerationMode::ETimer2WaveFormGenerationMode waveFormGenerationMode, Timer2CompareOutputMode::ETimer2CompareOutputMode compareOutputMode, Timer2Prescaller::ETimer2Prescaller prescaller)
    {
        unsigned char tccr2 = 0;
        
        switch(waveFormGenerationMode)
        {
            case Timer2WaveFormGenerationMode::PhaseCorrectPwm:
            tccr2 |= (1 << WGM20);
            break;
            case Timer2WaveFormGenerationMode::Ctc:
            tccr2 |= (1 << WGM21);
            break;
            case Timer2WaveFormGenerationMode::FastPwm:
            tccr2 |= ((1 << WGM21) | (1 << WGM20));
            break;
            case Timer2WaveFormGenerationMode::Normal:
            default:
            break;
        }
        
        switch(compareOutputMode)
        {
            case Timer2CompareOutputMode::ToggleOc0OnCompareMatch:
            tccr2 |= (1 << COM20);
            break;
            case Timer2CompareOutputMode::ClearOc0OnCompareMatch:
            tccr2 |= (1 << COM21);
            break;
            case Timer2CompareOutputMode::SetOc0OnCompareMatch:
            tccr2 |= ((1 << COM21) | (1 << COM20));
            break;
            case Timer2CompareOutputMode::NormalPortOperation:
            default:
            break;
        }
        
        switch(prescaller)
        {
            case Timer2Prescaller::DividedBy1:
            tccr2 |= (1 << CS20);
            break;
            case Timer2Prescaller::DividedBy8:
            tccr2 |= (1 << CS21);
            break;
            case Timer2Prescaller::DividedBy64:
            tccr2 |= ((1 << CS21) | (1 << CS20));
            break;
            case Timer2Prescaller::DividedBy256:
            tccr2 |= (1 << CS22);
            break;
            case Timer2Prescaller::DividedBy1024:
            tccr2 |= ((1 << CS22) | (1 << CS20));
            break;
            case Timer2Prescaller::ExternalCloclSourceOnT2OnFallingEdge:
            tccr2 |= ((1 << CS22) | (1 << CS21));
            break;
            case Timer2Prescaller::ExternalClockSourceOnT2OnRisingEdge:
            tccr2 |= ((1 << CS22) | (1 << CS21) | (1 << CS20));
            break;
            case Timer2Prescaller::NoClockSource:
            default:
            break;
        }
        
        TCCR2 = tccr2;
    }

    void Timer2::SetValue(unsigned char value)
    {
        TCNT2 = value;
    }

    unsigned char Timer2::GetValue( void )
    {
        return TCNT2;
    }

    void Timer2::SetCompareRegister(unsigned char value)
    {
        OCR2 = value;
    }

    unsigned char Timer2::GetCompareRegister()
    {
        return OCR2;
    }

    void Timer2::EnableOverflowInterrupt()
    {
        TIMSK |= (1 << TOIE2);
    }

    void Timer2::DisableOverflowInterrupt()
    {
        TIMSK &= ~(1 << TOIE2);
    }

    void Timer2::EnableCompareMatchInterrupt()
    {
        TIMSK |= (1 << OCIE2);
    }

    void Timer2::DisableCompareMatchInterrupt()
    {
        TIMSK &= ~(1 << OCIE2);
    }

    void Timer2::SetOverflowInterruptHandler(InterruptHandler handler)
    {
        _overflowInterruptHandler = handler;
    }

    void Timer2::SetCompareMatchInterruptHandler(InterruptHandler handler)
    {
        _compareMatchInterruptHandler = handler;
    }

    void Timer2::Vector9( void )
    {
        _compareMatchInterruptHandler();
    }

    void Timer2::Vector10( void )
    {
        _overflowInterruptHandler();
    }

    void __vector_9( void )
    {
        Timer2::_instance->Vector9();
    }

    void __vector_10( void )
    {
        Timer2::_instance->Vector10();
    }
};