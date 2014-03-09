/*
* pin_interrupt.cpp
*
* Created: 1/20/2013 3:32:20 PM
*  Author: muhammad
*/

#include "../inc/pin_interrupt.h"
#include <util/delay.h>

#define DEBOUNCE_TIMEOUT 10 // 10 milliseconds

namespace hal
{
    PinInterrupt* PinInterrupt::_instance = NULL;
    
    //************************************
    // Method:    PinInterrupt
    // FullName:  hal::PinInterrupt::PinInterrupt
    // Access:    private
    // Returns:
    // Qualifier:
    // Parameter: void
    //************************************
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

    //************************************
    // Method:    GetInstance
    // FullName:  hal::PinInterrupt::GetInstance
    // Access:    public static
    // Returns:   PinInterrupt*
    // Qualifier:
    // Parameter: void
    //************************************
    PinInterrupt* PinInterrupt::GetInstance( void )
    {
        if(_instance == NULL)
        {
            static PinInterrupt object;
            _instance = &object;
        }
        
        return _instance;
    }

    //************************************
    // Method:    Vector1
    // FullName:  hal::PinInterrupt::Vector1
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
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

    //************************************
    // Method:    Vector2
    // FullName:  hal::PinInterrupt::Vector2
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
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

    //************************************
    // Method:    Vector3
    // FullName:  hal::PinInterrupt::Vector3
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
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

    //************************************
    // Method:    Vector4
    // FullName:  hal::PinInterrupt::Vector4
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
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

    //************************************
    // Method:    Vector5
    // FullName:  hal::PinInterrupt::Vector5
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
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

    //************************************
    // Method:    Vector6
    // FullName:  hal::PinInterrupt::Vector6
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
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

    //************************************
    // Method:    Vector7
    // FullName:  hal::PinInterrupt::Vector7
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
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

    //************************************
    // Method:    Vector8
    // FullName:  hal::PinInterrupt::Vector8
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
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

    //************************************
    // Method:    SetInterrupt0Handler
    // FullName:  hal::PinInterrupt::SetInterrupt0Handler
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptHandler handler
    //************************************
    void PinInterrupt::SetInterrupt0Handler( InterruptHandler handler )
    {
        _int0InterruptHandler = handler;
    }

    //************************************
    // Method:    SetInterrupt1Handler
    // FullName:  hal::PinInterrupt::SetInterrupt1Handler
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptHandler handler
    //************************************
    void PinInterrupt::SetInterrupt1Handler( InterruptHandler handler )
    {
        _int1InterruptHandler = handler;
    }

    //************************************
    // Method:    SetInterrupt2Handler
    // FullName:  hal::PinInterrupt::SetInterrupt2Handler
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptHandler handler
    //************************************
    void PinInterrupt::SetInterrupt2Handler( InterruptHandler handler )
    {
        _int2InterruptHandler = handler;
    }

    //************************************
    // Method:    SetInterrupt3Handler
    // FullName:  hal::PinInterrupt::SetInterrupt3Handler
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptHandler handler
    //************************************
    void PinInterrupt::SetInterrupt3Handler( InterruptHandler handler )
    {
        _int3InterruptHandler = handler;
    }

    //************************************
    // Method:    SetInterrupt4Handler
    // FullName:  hal::PinInterrupt::SetInterrupt4Handler
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptHandler handler
    //************************************
    void PinInterrupt::SetInterrupt4Handler( InterruptHandler handler )
    {
        _int4InterruptHandler = handler;
    }

    //************************************
    // Method:    SetInterrupt5Handler
    // FullName:  hal::PinInterrupt::SetInterrupt5Handler
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptHandler handler
    //************************************
    void PinInterrupt::SetInterrupt5Handler( InterruptHandler handler )
    {
        _int5InterruptHandler = handler;
    }
    
    void PinInterrupt::SetInterrupt5ReleasedHandler( InterruptHandler handler )
    {
        _int5ReleasedInterruptHandler = handler;
    }

    //************************************
    // Method:    SetInterrupt6Handler
    // FullName:  hal::PinInterrupt::SetInterrupt6Handler
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptHandler handler
    //************************************
    void PinInterrupt::SetInterrupt6Handler( InterruptHandler handler )
    {
        _int6InterruptHandler = handler;
    }
    
    void PinInterrupt::SetInterrupt6ReleasedHandler( InterruptHandler handler )
    {
        _int6ReleasedInterruptHandler = handler;
    }

    //************************************
    // Method:    SetInterrupt7Handler
    // FullName:  hal::PinInterrupt::SetInterrupt7Handler
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptHandler handler
    //************************************
    void PinInterrupt::SetInterrupt7Handler( InterruptHandler handler )
    {
        _int7InterruptHandler = handler;
    }

    //************************************
    // Method:    SetInterrupt0Mode
    // FullName:  hal::PinInterrupt::SetInterrupt0Mode
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
    //************************************
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

    //************************************
    // Method:    SetInterrupt1Mode
    // FullName:  hal::PinInterrupt::SetInterrupt1Mode
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
    //************************************
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

    //************************************
    // Method:    SetInterrupt2Mode
    // FullName:  hal::PinInterrupt::SetInterrupt2Mode
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
    //************************************
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

    //************************************
    // Method:    SetInterrupt3Mode
    // FullName:  hal::PinInterrupt::SetInterrupt3Mode
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
    //************************************
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

    //************************************
    // Method:    SetInterrupt4Mode
    // FullName:  hal::PinInterrupt::SetInterrupt4Mode
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
    //************************************
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

    //************************************
    // Method:    SetInterrupt5Mode
    // FullName:  hal::PinInterrupt::SetInterrupt5Mode
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
    //************************************
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

    //************************************
    // Method:    SetInterrupt6Mode
    // FullName:  hal::PinInterrupt::SetInterrupt6Mode
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
    //************************************
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

    //************************************
    // Method:    SetInterrupt7Mode
    // FullName:  hal::PinInterrupt::SetInterrupt7Mode
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
    //************************************
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

    //************************************
    // Method:    EnableInterrupt0
    // FullName:  hal::PinInterrupt::EnableInterrupt0
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::EnableInterrupt0( void )
    {
        EIMSK |= (1 << INT0);
    }

    //************************************
    // Method:    EnableInterrupt1
    // FullName:  hal::PinInterrupt::EnableInterrupt1
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::EnableInterrupt1( void )
    {
        EIMSK |= (1 << INT1);
    }

    //************************************
    // Method:    EnableInterrupt2
    // FullName:  hal::PinInterrupt::EnableInterrupt2
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::EnableInterrupt2( void )
    {
        EIMSK |= (1 << INT2);
    }

    //************************************
    // Method:    EnableInterrupt3
    // FullName:  hal::PinInterrupt::EnableInterrupt3
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::EnableInterrupt3( void )
    {
        EIMSK |= (1 << INT3);
    }

    //************************************
    // Method:    EnableInterrupt4
    // FullName:  hal::PinInterrupt::EnableInterrupt4
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::EnableInterrupt4( void )
    {
        EIMSK |= (1 << INT4);
    }

    //************************************
    // Method:    EnableInterrupt5
    // FullName:  hal::PinInterrupt::EnableInterrupt5
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::EnableInterrupt5( void )
    {
        EIMSK |= (1 << INT5);
    }

    //************************************
    // Method:    EnableInterrupt6
    // FullName:  hal::PinInterrupt::EnableInterrupt6
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::EnableInterrupt6( void )
    {
        EIMSK |= (1 << INT6);
    }

    //************************************
    // Method:    EnableInterrupt7
    // FullName:  hal::PinInterrupt::EnableInterrupt7
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::EnableInterrupt7( void )
    {
        EIMSK |= (1 << INT7);
    }

    //************************************
    // Method:    DisableInterrupt0
    // FullName:  hal::PinInterrupt::DisableInterrupt0
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::DisableInterrupt0( void )
    {
        EIMSK &= ~(1 << INT0);
    }

    //************************************
    // Method:    DisableInterrupt1
    // FullName:  hal::PinInterrupt::DisableInterrupt1
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::DisableInterrupt1( void )
    {
        EIMSK &= ~(1 << INT1);
    }

    //************************************
    // Method:    DisableInterrupt2
    // FullName:  hal::PinInterrupt::DisableInterrupt2
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::DisableInterrupt2( void )
    {
        EIMSK &= ~(1 << INT2);
    }

    //************************************
    // Method:    DisableInterrupt3
    // FullName:  hal::PinInterrupt::DisableInterrupt3
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::DisableInterrupt3( void )
    {
        EIMSK &= ~(1 << INT3);
    }

    //************************************
    // Method:    DisableInterrupt4
    // FullName:  hal::PinInterrupt::DisableInterrupt4
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::DisableInterrupt4( void )
    {
        EIMSK &= ~(1 << INT4);
    }

    //************************************
    // Method:    DisableInterrupt5
    // FullName:  hal::PinInterrupt::DisableInterrupt5
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::DisableInterrupt5( void )
    {
        EIMSK &= ~(1 << INT5);
    }

    //************************************
    // Method:    DisableInterrupt6
    // FullName:  hal::PinInterrupt::DisableInterrupt6
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::DisableInterrupt6( void )
    {
        EIMSK &= ~(1 << INT6);
    }

    //************************************
    // Method:    DisableInterrupt7
    // FullName:  hal::PinInterrupt::DisableInterrupt7
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::DisableInterrupt7( void )
    {
        EIMSK &= ~(1 << INT7);
    }

    //************************************
    // Method:    ClearInterrupt0Flag
    // FullName:  hal::PinInterrupt::ClearInterrupt0Flag
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::ClearInterrupt0Flag( void )
    {
        EIFR |= (1 << INTF0);
    }

    //************************************
    // Method:    ClearInterrupt1Flag
    // FullName:  hal::PinInterrupt::ClearInterrupt1Flag
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::ClearInterrupt1Flag( void )
    {
        EIFR |= (1 << INTF1);
    }

    //************************************
    // Method:    ClearInterrupt2Flag
    // FullName:  hal::PinInterrupt::ClearInterrupt2Flag
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::ClearInterrupt2Flag( void )
    {
        EIFR |= (1 << INTF2);
    }

    //************************************
    // Method:    ClearInterrupt3Flag
    // FullName:  hal::PinInterrupt::ClearInterrupt3Flag
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::ClearInterrupt3Flag( void )
    {
        EIFR |= (1 << INTF3);
    }

    //************************************
    // Method:    ClearInterrupt4Flag
    // FullName:  hal::PinInterrupt::ClearInterrupt4Flag
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::ClearInterrupt4Flag( void )
    {
        EIFR |= (1 << INTF4);
    }

    //************************************
    // Method:    ClearInterrupt5Flag
    // FullName:  hal::PinInterrupt::ClearInterrupt5Flag
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::ClearInterrupt5Flag( void )
    {
        EIFR |= (1 << INTF5);
    }

    //************************************
    // Method:    ClearInterrupt6Flag
    // FullName:  hal::PinInterrupt::ClearInterrupt6Flag
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::ClearInterrupt6Flag( void )
    {
        EIFR |= (1 << INTF6);
    }

    //************************************
    // Method:    ClearInterrupt7Flag
    // FullName:  hal::PinInterrupt::ClearInterrupt7Flag
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void PinInterrupt::ClearInterrupt7Flag( void )
    {
        EIFR |= (1 << INTF7);
    }

    void PinInterrupt::HandleDebounce( void )
    {
        _delay_ms(DEBOUNCE_TIMEOUT);
    }

    //************************************
    // Method:    __vector_1
    // FullName:  hal::__vector_1
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void __vector_1( void )
    {
        PinInterrupt::_instance->Vector1();
    }

    //************************************
    // Method:    __vector_2
    // FullName:  hal::__vector_2
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void __vector_2( void )
    {
        PinInterrupt::_instance->Vector2();
    }

    //************************************
    // Method:    __vector_3
    // FullName:  hal::__vector_3
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void __vector_3( void )
    {
        PinInterrupt::_instance->Vector3();
    }

    //************************************
    // Method:    __vector_4
    // FullName:  hal::__vector_4
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void __vector_4( void )
    {
        PinInterrupt::_instance->Vector4();
    }

    //************************************
    // Method:    __vector_5
    // FullName:  hal::__vector_5
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void __vector_5( void )
    {
        PinInterrupt::_instance->Vector5();
    }

    //************************************
    // Method:    __vector_6
    // FullName:  hal::__vector_6
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void __vector_6( void )
    {
        PinInterrupt::_instance->Vector6();
    }

    //************************************
    // Method:    __vector_7
    // FullName:  hal::__vector_7
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void __vector_7( void )
    {
        PinInterrupt::_instance->Vector7();
    }

    //************************************
    // Method:    __vector_8
    // FullName:  hal::__vector_8
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void __vector_8( void )
    {
        PinInterrupt::_instance->Vector8();
    }

};