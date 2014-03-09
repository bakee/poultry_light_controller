#include "../inc/pin_interrupt.h"
#include <util/delay.h>

#define DEBOUNCE_TIMEOUT 10 // 10 milliseconds

namespace hal
{
    PinInterrupt* PinInterrupt::_instance = NULL;
    
    PinInterrupt::PinInterrupt( void )
    {
        _int0InterruptHandler = NULL;
        _int1InterruptHandler = NULL;
        _int2InterruptHandler = NULL;
        _int3InterruptHandler = NULL;
        _int4InterruptHandler = NULL;
        _int5InterruptHandler = NULL;
        _int5ReleasedInterruptHandler = NULL;
        _int6InterruptHandler = NULL;
        _int6ReleasedInterruptHandler = NULL;
        _int7InterruptHandler = NULL;
        
        // Enable internal pull-ups
        PORTD |= ((1 << INT0) | (1 << INT1) | (1 << INT2) | (1 << INT3));
        PORTE |= ((1 << INT4) | (1 << INT5) | (1 << INT6) | (1 << INT7));
    }

    PinInterrupt* PinInterrupt::GetInstance( void )
    {
        if(_instance == NULL)
        {
            static PinInterrupt object;
            _instance = &object;
        }
        
        return _instance;
    }

    void PinInterrupt::Vector1( void )
    {
        if(_int0InterruptHandler != NULL)
        {
            HandleDebounce();
            if((PINE & (1 << PINE0)) == 0)
            {
                _int0InterruptHandler();
            }
        }
    }

    void PinInterrupt::Vector2( void )
    {
        if(_int1InterruptHandler != NULL)
        {
            HandleDebounce();
            if((PINE & (1 << PINE1)) == 0)
            {
                _int1InterruptHandler();
            }
        }
    }

    void PinInterrupt::Vector3( void )
    {
        if(_int2InterruptHandler != NULL)
        {
            HandleDebounce();
            if((PINE & (1 << PINE2)) == 0)
            {
                _int2InterruptHandler();
            }
        }
    }

    void PinInterrupt::Vector4( void )
    {
        if(_int3InterruptHandler != NULL)
        {
            HandleDebounce();
            if((PINE & (1 << PINE3)) == 0)
            {
                _int3InterruptHandler();
            }
        }
    }

    void PinInterrupt::Vector5( void )
    {
        if(_int4InterruptHandler != NULL)
        {
            HandleDebounce();
            if((PINE & (1 << PINE4)) == 0)
            {
                _int4InterruptHandler();
            }
        }
    }

    void PinInterrupt::Vector6( void )
    {
        HandleDebounce();
        if((PINE & (1 << PINE5)) == 0)
        {
            if(_int5InterruptHandler != NULL)
            {
                _int5InterruptHandler();
            }
        }
        else
        {
            if(_int5ReleasedInterruptHandler != NULL)
            {
                _int5ReleasedInterruptHandler();
            }
        }
    }

    void PinInterrupt::Vector7( void )
    {
        HandleDebounce();
        if((PINE & (1 << PINE6)) == 0)
        {
            if(_int6InterruptHandler != NULL)
            {
                _int6InterruptHandler();
            }
        }
        else
        {
            if(_int6ReleasedInterruptHandler != NULL)
            {
                _int6ReleasedInterruptHandler();
            }
        }
    }

    void PinInterrupt::Vector8( void )
    {
        if(_int7InterruptHandler != NULL)
        {
            HandleDebounce();
            if((PINE & (1 << PINE7)) == 0)
            {
                _int7InterruptHandler();
            }
        }
    }

    void PinInterrupt::SetInterrupt0Handler( InterruptHandler handler )
    {
        _int0InterruptHandler = handler;
    }

    void PinInterrupt::SetInterrupt1Handler( InterruptHandler handler )
    {
        _int1InterruptHandler = handler;
    }

    void PinInterrupt::SetInterrupt2Handler( InterruptHandler handler )
    {
        _int2InterruptHandler = handler;
    }

    void PinInterrupt::SetInterrupt3Handler( InterruptHandler handler )
    {
        _int3InterruptHandler = handler;
    }

    void PinInterrupt::SetInterrupt4Handler( InterruptHandler handler )
    {
        _int4InterruptHandler = handler;
    }

    void PinInterrupt::SetInterrupt5Handler( InterruptHandler handler )
    {
        _int5InterruptHandler = handler;
    }
    
    void PinInterrupt::SetInterrupt5ReleasedHandler( InterruptHandler handler )
    {
        _int5ReleasedInterruptHandler = handler;
    }

    void PinInterrupt::SetInterrupt6Handler( InterruptHandler handler )
    {
        _int6InterruptHandler = handler;
    }
    
    void PinInterrupt::SetInterrupt6ReleasedHandler( InterruptHandler handler )
    {
        _int6ReleasedInterruptHandler = handler;
    }

    void PinInterrupt::SetInterrupt7Handler( InterruptHandler handler )
    {
        _int7InterruptHandler = handler;
    }

    void PinInterrupt::SetInterrupt0Mode( InterruptSenseControl::EInterruptSenseControl interruptMode )
    {
        unsigned char eicra = EICRA & 0xFC;
        switch(interruptMode)
        {
            case InterruptSenseControl::InterruptOnFallingEdge:
            eicra |= (1 << ISC01);
            break;
            case InterruptSenseControl::InterruptOnRisingEdge:
            eicra |= ((1 << ISC01) | (1 << ISC00));
            break;
            case InterruptSenseControl::InterruptOnLowLevel:
            case InterruptSenseControl::InterruptOnBothEdge:
            default:
            break;
        }
        
        EICRA = eicra;
    }

    void PinInterrupt::SetInterrupt1Mode( InterruptSenseControl::EInterruptSenseControl interruptMode )
    {
        unsigned char eicra = EICRA & 0xF3;
        switch(interruptMode)
        {
            case InterruptSenseControl::InterruptOnFallingEdge:
            eicra |= (1 << ISC11);
            break;
            case InterruptSenseControl::InterruptOnRisingEdge:
            eicra |= ((1 << ISC11) | (1 << ISC10));
            break;
            case InterruptSenseControl::InterruptOnLowLevel:
            case InterruptSenseControl::InterruptOnBothEdge:
            default:
            break;
        }
        
        EICRA = eicra;
    }

    void PinInterrupt::SetInterrupt2Mode( InterruptSenseControl::EInterruptSenseControl interruptMode )
    {
        unsigned char eicra = EICRA & 0xCF;
        switch(interruptMode)
        {
            case InterruptSenseControl::InterruptOnFallingEdge:
            eicra |= (1 << ISC21);
            break;
            case InterruptSenseControl::InterruptOnRisingEdge:
            eicra |= ((1 << ISC21) | (1 << ISC20));
            break;
            case InterruptSenseControl::InterruptOnLowLevel:
            case InterruptSenseControl::InterruptOnBothEdge:
            default:
            break;
        }
        
        EICRA = eicra;
    }

    void PinInterrupt::SetInterrupt3Mode( InterruptSenseControl::EInterruptSenseControl interruptMode )
    {
        unsigned char eicra = EICRA & 0x3F;
        switch(interruptMode)
        {
            case InterruptSenseControl::InterruptOnFallingEdge:
            eicra |= (1 << ISC31);
            break;
            case InterruptSenseControl::InterruptOnRisingEdge:
            eicra |= ((1 << ISC31) | (1 << ISC30));
            break;
            case InterruptSenseControl::InterruptOnLowLevel:
            case InterruptSenseControl::InterruptOnBothEdge:
            default:
            break;
        }
        
        EICRA = eicra;
    }

    void PinInterrupt::SetInterrupt4Mode( InterruptSenseControl::EInterruptSenseControl interruptMode )
    {
        unsigned char eicrb = EICRB & 0xFC;
        switch(interruptMode)
        {
            case InterruptSenseControl::InterruptOnBothEdge:
            eicrb |= (1 << ISC40);
            break;
            case InterruptSenseControl::InterruptOnFallingEdge:
            eicrb |= (1 << ISC41);
            break;
            case InterruptSenseControl::InterruptOnRisingEdge:
            eicrb |= ((1 << ISC41) | (1 << ISC40));
            break;
            case InterruptSenseControl::InterruptOnLowLevel:
            default:
            break;
        }
        
        EICRB = eicrb;
    }

    void PinInterrupt::SetInterrupt5Mode( InterruptSenseControl::EInterruptSenseControl interruptMode )
    {
        unsigned char eicrb = EICRB & 0xF3;
        switch(interruptMode)
        {
            case InterruptSenseControl::InterruptOnBothEdge:
            eicrb |= (1 << ISC50);
            break;
            case InterruptSenseControl::InterruptOnFallingEdge:
            eicrb |= (1 << ISC51);
            break;
            case InterruptSenseControl::InterruptOnRisingEdge:
            eicrb |= ((1 << ISC51) | (1 << ISC50));
            break;
            case InterruptSenseControl::InterruptOnLowLevel:
            default:
            break;
        }
        
        EICRB = eicrb;
    }

    void PinInterrupt::SetInterrupt6Mode( InterruptSenseControl::EInterruptSenseControl interruptMode )
    {
        unsigned char eicrb = EICRB & 0xCF;
        switch(interruptMode)
        {
            case InterruptSenseControl::InterruptOnBothEdge:
            eicrb |= (1 << ISC60);
            break;
            case InterruptSenseControl::InterruptOnFallingEdge:
            eicrb |= (1 << ISC61);
            break;
            case InterruptSenseControl::InterruptOnRisingEdge:
            eicrb |= ((1 << ISC61) | (1 << ISC60));
            break;
            case InterruptSenseControl::InterruptOnLowLevel:
            default:
            break;
        }
        
        EICRB = eicrb;
    }

    void PinInterrupt::SetInterrupt7Mode( InterruptSenseControl::EInterruptSenseControl interruptMode )
    {
        unsigned char eicrb = EICRB & 0x3F;
        switch(interruptMode)
        {
            case InterruptSenseControl::InterruptOnBothEdge:
            eicrb |= (1 << ISC70);
            break;
            case InterruptSenseControl::InterruptOnFallingEdge:
            eicrb |= (1 << ISC71);
            break;
            case InterruptSenseControl::InterruptOnRisingEdge:
            eicrb |= ((1 << ISC71) | (1 << ISC70));
            break;
            case InterruptSenseControl::InterruptOnLowLevel:
            default:
            break;
        }
        
        EICRB = eicrb;
    }

    void PinInterrupt::EnableInterrupt0( void )
    {
        EIMSK |= (1 << INT0);
    }

    void PinInterrupt::EnableInterrupt1( void )
    {
        EIMSK |= (1 << INT1);
    }

    void PinInterrupt::EnableInterrupt2( void )
    {
        EIMSK |= (1 << INT2);
    }

    void PinInterrupt::EnableInterrupt3( void )
    {
        EIMSK |= (1 << INT3);
    }

    void PinInterrupt::EnableInterrupt4( void )
    {
        EIMSK |= (1 << INT4);
    }

    void PinInterrupt::EnableInterrupt5( void )
    {
        EIMSK |= (1 << INT5);
    }

    void PinInterrupt::EnableInterrupt6( void )
    {
        EIMSK |= (1 << INT6);
    }

    void PinInterrupt::EnableInterrupt7( void )
    {
        EIMSK |= (1 << INT7);
    }

    void PinInterrupt::DisableInterrupt0( void )
    {
        EIMSK &= ~(1 << INT0);
    }

    void PinInterrupt::DisableInterrupt1( void )
    {
        EIMSK &= ~(1 << INT1);
    }

    void PinInterrupt::DisableInterrupt2( void )
    {
        EIMSK &= ~(1 << INT2);
    }

    void PinInterrupt::DisableInterrupt3( void )
    {
        EIMSK &= ~(1 << INT3);
    }

    void PinInterrupt::DisableInterrupt4( void )
    {
        EIMSK &= ~(1 << INT4);
    }

    void PinInterrupt::DisableInterrupt5( void )
    {
        EIMSK &= ~(1 << INT5);
    }

    void PinInterrupt::DisableInterrupt6( void )
    {
        EIMSK &= ~(1 << INT6);
    }

    void PinInterrupt::DisableInterrupt7( void )
    {
        EIMSK &= ~(1 << INT7);
    }

    void PinInterrupt::ClearInterrupt0Flag( void )
    {
        EIFR |= (1 << INTF0);
    }

    void PinInterrupt::ClearInterrupt1Flag( void )
    {
        EIFR |= (1 << INTF1);
    }

    void PinInterrupt::ClearInterrupt2Flag( void )
    {
        EIFR |= (1 << INTF2);
    }

    void PinInterrupt::ClearInterrupt3Flag( void )
    {
        EIFR |= (1 << INTF3);
    }

    void PinInterrupt::ClearInterrupt4Flag( void )
    {
        EIFR |= (1 << INTF4);
    }

    void PinInterrupt::ClearInterrupt5Flag( void )
    {
        EIFR |= (1 << INTF5);
    }

    void PinInterrupt::ClearInterrupt6Flag( void )
    {
        EIFR |= (1 << INTF6);
    }

    void PinInterrupt::ClearInterrupt7Flag( void )
    {
        EIFR |= (1 << INTF7);
    }

    void PinInterrupt::HandleDebounce( void )
    {
        _delay_ms(DEBOUNCE_TIMEOUT);
    }

    void __vector_1( void )
    {
        PinInterrupt::_instance->Vector1();
    }

    void __vector_2( void )
    {
        PinInterrupt::_instance->Vector2();
    }

    void __vector_3( void )
    {
        PinInterrupt::_instance->Vector3();
    }

    void __vector_4( void )
    {
        PinInterrupt::_instance->Vector4();
    }

    void __vector_5( void )
    {
        PinInterrupt::_instance->Vector5();
    }

    void __vector_6( void )
    {
        PinInterrupt::_instance->Vector6();
    }

    void __vector_7( void )
    {
        PinInterrupt::_instance->Vector7();
    }

    void __vector_8( void )
    {
        PinInterrupt::_instance->Vector8();
    }

};