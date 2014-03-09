/*
* timer2.cpp
*
* Created: 1/13/2013 5:16:06 PM
*  Author: muhammad
*/

#include "../inc/timer2.h"
#include <avr/io.h>

namespace hal
{
    Timer2* Timer2::_instance = NULL;

    //************************************
    // Method:    Timer2
    // FullName:  hal::Timer2::Timer2
    // Access:    public
    // Returns:
    // Qualifier:
    //************************************
    Timer2::Timer2()
    {
        _compareMatchInterruptHandler = NULL;
        _overflowInterruptHandler = NULL;
    }
    
    //************************************
    // Method:    GetInstance
    // FullName:  hal::Timer2::GetInstance
    // Access:    public
    // Returns:   Timer2*
    // Qualifier:
    //************************************
    Timer2* Timer2::GetInstance()
    {
        if(_instance == NULL)
        {
            static Timer2 object;
            _instance = &object;
        }
        
        return _instance;
    }

    //************************************
    // Method:    Configure
    // FullName:  hal::Timer2::Configure
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: Timer2WaveFormGenerationMode waveFormGenerationMode
    // Parameter: Timer2CompareOutputMode compareOutputMode
    // Parameter: Timer2Prescaller prescaller
    // Parameter: bool isAsynchronousMode
    //************************************
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

    //************************************
    // Method:    SetValue
    // FullName:  hal::Timer2::SetValue
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: unsigned char value
    //************************************
    void Timer2::SetValue(unsigned char value)
    {
        TCNT2 = value;
    }

    //************************************
    // Method:    GetValue
    // FullName:  hal::Timer2::GetValue
    // Access:    public
    // Returns:   unsigned char
    // Qualifier:
    // Parameter: void
    //************************************
    unsigned char Timer2::GetValue( void )
    {
        return TCNT2;
    }

    //************************************
    // Method:    SetCompareRegister
    // FullName:  hal::Timer2::SetCompareRegister
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: unsigned char value
    //************************************
    void Timer2::SetCompareRegister(unsigned char value)
    {
        OCR2 = value;
    }

    //************************************
    // Method:    GetCompareRegister
    // FullName:  hal::Timer2::GetCompareRegister
    // Access:    public
    // Returns:   unsigned char
    // Qualifier:
    //************************************
    unsigned char Timer2::GetCompareRegister()
    {
        return OCR2;
    }

    //************************************
    // Method:    EnableOverflowInterrupt
    // FullName:  hal::Timer2::EnableOverflowInterrupt
    // Access:    public
    // Returns:   void
    // Qualifier:
    //************************************
    void Timer2::EnableOverflowInterrupt()
    {
        TIMSK |= (1 << TOIE2);
    }

    //************************************
    // Method:    DisableOverflowInterrupt
    // FullName:  hal::Timer2::DisableOverflowInterrupt
    // Access:    public
    // Returns:   void
    // Qualifier:
    //************************************
    void Timer2::DisableOverflowInterrupt()
    {
        TIMSK &= ~(1 << TOIE2);
    }

    //************************************
    // Method:    EnableCompareMatchInterrupt
    // FullName:  hal::Timer2::EnableCompareMatchInterrupt
    // Access:    public
    // Returns:   void
    // Qualifier:
    //************************************
    void Timer2::EnableCompareMatchInterrupt()
    {
        TIMSK |= (1 << OCIE2);
    }
    
    //************************************
    // Method:    DisableCompareMatchInterrupt
    // FullName:  hal::Timer2::DisableCompareMatchInterrupt
    // Access:    public
    // Returns:   void
    // Qualifier:
    //************************************
    void Timer2::DisableCompareMatchInterrupt()
    {
        TIMSK &= ~(1 << OCIE2);
    }

    //************************************
    // Method:    SetOverflowInterruptHandler
    // FullName:  hal::Timer2::SetOverflowInterruptHandler
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptHandler handler
    //************************************
    void Timer2::SetOverflowInterruptHandler(InterruptHandler handler)
    {
        _overflowInterruptHandler = handler;
    }

    //************************************
    // Method:    SetCompareMatchInterruptHandler
    // FullName:  hal::Timer2::SetCompareMatchInterruptHandler
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptHandler handler
    //************************************
    void Timer2::SetCompareMatchInterruptHandler(InterruptHandler handler)
    {
        _compareMatchInterruptHandler = handler;
    }

    //************************************
    // Method:    Vector9
    // FullName:  hal::Timer2::Vector9
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Timer2::Vector9( void )
    {
        _compareMatchInterruptHandler();
    }

    //************************************
    // Method:    Vector10
    // FullName:  hal::Timer2::Vector10
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Timer2::Vector10( void )
    {
        _overflowInterruptHandler();
    }

    //************************************
    // Method:    __vector_9
    // FullName:  hal::__vector_9
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void __vector_9( void )
    {
        Timer2::_instance->Vector9();
    }

    //************************************
    // Method:    __vector_10
    // FullName:  hal::__vector_10
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void __vector_10( void )
    {
        Timer2::_instance->Vector10();
    }
};