/*
* pin_interrupt.h
*
* Created: 1/20/2013 3:32:06 PM
*  Author: muhammad
*/


#ifndef PIN_INTERRUPT_H_
#define PIN_INTERRUPT_H_

#include "../inc/hal_utils.h"

namespace hal
{
    class InterruptSenseControl
    {
        public:
        typedef enum
        {
            InterruptOnLowLevel,
            InterruptOnBothEdge,
            InterruptOnFallingEdge,
            InterruptOnRisingEdge
        } EInterruptSenseControl;
    };
    
    class PinInterrupt
    {
        private:
        
        static PinInterrupt* _instance;
        
        InterruptHandler _int0InterruptHandler;
        
        InterruptHandler _int1InterruptHandler;
        
        InterruptHandler _int2InterruptHandler;
        
        InterruptHandler _int3InterruptHandler;
        
        InterruptHandler _int4InterruptHandler;
        
        InterruptHandler _int5InterruptHandler;
        InterruptHandler _int5ReleasedInterruptHandler;
                
        InterruptHandler _int6InterruptHandler;
        InterruptHandler _int6ReleasedInterruptHandler;
        
        InterruptHandler _int7InterruptHandler;
        
        //************************************
        // Method:    PinInterrupt
        // FullName:  hal::PinInterrupt::PinInterrupt
        // Access:    private
        // Returns:
        // Qualifier:
        // Parameter: void
        //************************************
        PinInterrupt( void );
        
        void HandleDebounce( void );
        
        //************************************
        // Method:    Vector1
        // FullName:  hal::PinInterrupt::Vector1
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Vector1( void );
        
        //************************************
        // Method:    Vector2
        // FullName:  hal::PinInterrupt::Vector2
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Vector2( void );
        
        //************************************
        // Method:    Vector3
        // FullName:  hal::PinInterrupt::Vector3
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Vector3( void );
        
        //************************************
        // Method:    Vector4
        // FullName:  hal::PinInterrupt::Vector4
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Vector4( void );
        
        //************************************
        // Method:    Vector5
        // FullName:  hal::PinInterrupt::Vector5
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Vector5( void );
        
        //************************************
        // Method:    Vector6
        // FullName:  hal::PinInterrupt::Vector6
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Vector6( void );
        
        //************************************
        // Method:    Vector7
        // FullName:  hal::PinInterrupt::Vector7
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Vector7( void );
        
        //************************************
        // Method:    Vector8
        // FullName:  hal::PinInterrupt::Vector8
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Vector8( void );
        
        public:
        
        //************************************
        // Method:    GetInstance
        // FullName:  hal::PinInterrupt::GetInstance
        // Access:    public static
        // Returns:   PinInterrupt*
        // Qualifier:
        // Parameter: void
        //************************************
        static PinInterrupt* GetInstance( void );
        
        //************************************
        // Method:    SetInterrupt0Handler
        // FullName:  hal::PinInterrupt::SetInterrupt0Handler
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptHandler handler
        //************************************
        void SetInterrupt0Handler(InterruptHandler handler);
        
        //************************************
        // Method:    SetInterrupt1Handler
        // FullName:  hal::PinInterrupt::SetInterrupt1Handler
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptHandler handler
        //************************************
        void SetInterrupt1Handler(InterruptHandler handler);
        
        //************************************
        // Method:    SetInterrupt2Handler
        // FullName:  hal::PinInterrupt::SetInterrupt2Handler
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptHandler handler
        //************************************
        void SetInterrupt2Handler(InterruptHandler handler);
        
        //************************************
        // Method:    SetInterrupt3Handler
        // FullName:  hal::PinInterrupt::SetInterrupt3Handler
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptHandler handler
        //************************************
        void SetInterrupt3Handler(InterruptHandler handler);
        
        //************************************
        // Method:    SetInterrupt4Handler
        // FullName:  hal::PinInterrupt::SetInterrupt4Handler
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptHandler handler
        //************************************
        void SetInterrupt4Handler(InterruptHandler handler);
        
        //************************************
        // Method:    SetInterrupt5Handler
        // FullName:  hal::PinInterrupt::SetInterrupt5Handler
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptHandler handler
        //************************************
        void SetInterrupt5Handler(InterruptHandler handler);
        void SetInterrupt5ReleasedHandler(InterruptHandler handler);        
        
        //************************************
        // Method:    SetInterrupt6Handler
        // FullName:  hal::PinInterrupt::SetInterrupt6Handler
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptHandler handler
        //************************************
        void SetInterrupt6Handler(InterruptHandler handler);
        void SetInterrupt6ReleasedHandler(InterruptHandler handler);        
        
        //************************************
        // Method:    SetInterrupt7Handler
        // FullName:  hal::PinInterrupt::SetInterrupt7Handler
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptHandler handler
        //************************************
        void SetInterrupt7Handler(InterruptHandler handler);
        
        //************************************
        // Method:    SetInterrupt0Mode
        // FullName:  hal::PinInterrupt::SetInterrupt0Mode
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
        //************************************
        void SetInterrupt0Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        //************************************
        // Method:    SetInterrupt1Mode
        // FullName:  hal::PinInterrupt::SetInterrupt1Mode
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
        //************************************
        void SetInterrupt1Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        //************************************
        // Method:    SetInterrupt2Mode
        // FullName:  hal::PinInterrupt::SetInterrupt2Mode
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
        //************************************
        void SetInterrupt2Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        //************************************
        // Method:    SetInterrupt3Mode
        // FullName:  hal::PinInterrupt::SetInterrupt3Mode
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
        //************************************
        void SetInterrupt3Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        //************************************
        // Method:    SetInterrupt4Mode
        // FullName:  hal::PinInterrupt::SetInterrupt4Mode
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
        //************************************
        void SetInterrupt4Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        //************************************
        // Method:    SetInterrupt5Mode
        // FullName:  hal::PinInterrupt::SetInterrupt5Mode
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
        //************************************
        void SetInterrupt5Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        //************************************
        // Method:    SetInterrupt6Mode
        // FullName:  hal::PinInterrupt::SetInterrupt6Mode
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
        //************************************
        void SetInterrupt6Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        //************************************
        // Method:    SetInterrupt7Mode
        // FullName:  hal::PinInterrupt::SetInterrupt7Mode
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: InterruptSenseControl::EInterruptSenseControl interruptMode
        //************************************
        void SetInterrupt7Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        //************************************
        // Method:    EnableInterrupt0
        // FullName:  hal::PinInterrupt::EnableInterrupt0
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void EnableInterrupt0( void );
        
        //************************************
        // Method:    EnableInterrupt1
        // FullName:  hal::PinInterrupt::EnableInterrupt1
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void EnableInterrupt1( void );
        
        //************************************
        // Method:    EnableInterrupt2
        // FullName:  hal::PinInterrupt::EnableInterrupt2
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void EnableInterrupt2( void );
        
        //************************************
        // Method:    EnableInterrupt3
        // FullName:  hal::PinInterrupt::EnableInterrupt3
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void EnableInterrupt3( void );
        
        //************************************
        // Method:    EnableInterrupt4
        // FullName:  hal::PinInterrupt::EnableInterrupt4
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void EnableInterrupt4( void );
        
        //************************************
        // Method:    EnableInterrupt5
        // FullName:  hal::PinInterrupt::EnableInterrupt5
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void EnableInterrupt5( void );
        
        //************************************
        // Method:    EnableInterrupt6
        // FullName:  hal::PinInterrupt::EnableInterrupt6
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void EnableInterrupt6( void );
        
        //************************************
        // Method:    EnableInterrupt7
        // FullName:  hal::PinInterrupt::EnableInterrupt7
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void EnableInterrupt7( void );
        
        //************************************
        // Method:    DisableInterrupt0
        // FullName:  hal::PinInterrupt::DisableInterrupt0
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void DisableInterrupt0( void );
        
        //************************************
        // Method:    DisableInterrupt1
        // FullName:  hal::PinInterrupt::DisableInterrupt1
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void DisableInterrupt1( void );
        
        //************************************
        // Method:    DisableInterrupt2
        // FullName:  hal::PinInterrupt::DisableInterrupt2
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void DisableInterrupt2( void );
        
        //************************************
        // Method:    DisableInterrupt3
        // FullName:  hal::PinInterrupt::DisableInterrupt3
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void DisableInterrupt3( void );
        
        //************************************
        // Method:    DisableInterrupt4
        // FullName:  hal::PinInterrupt::DisableInterrupt4
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void DisableInterrupt4( void );
        
        //************************************
        // Method:    DisableInterrupt5
        // FullName:  hal::PinInterrupt::DisableInterrupt5
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void DisableInterrupt5( void );
        
        //************************************
        // Method:    DisableInterrupt6
        // FullName:  hal::PinInterrupt::DisableInterrupt6
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void DisableInterrupt6( void );
        
        //************************************
        // Method:    DisableInterrupt7
        // FullName:  hal::PinInterrupt::DisableInterrupt7
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void DisableInterrupt7( void );
        
        //************************************
        // Method:    ClearInterrupt0Flag
        // FullName:  hal::PinInterrupt::ClearInterrupt0Flag
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void ClearInterrupt0Flag( void );
        
        //************************************
        // Method:    ClearInterrupt1Flag
        // FullName:  hal::PinInterrupt::ClearInterrupt1Flag
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void ClearInterrupt1Flag( void );
        
        //************************************
        // Method:    ClearInterrupt2Flag
        // FullName:  hal::PinInterrupt::ClearInterrupt2Flag
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void ClearInterrupt2Flag( void );
        
        //************************************
        // Method:    ClearInterrupt3Flag
        // FullName:  hal::PinInterrupt::ClearInterrupt3Flag
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void ClearInterrupt3Flag( void );
        
        //************************************
        // Method:    ClearInterrupt4Flag
        // FullName:  hal::PinInterrupt::ClearInterrupt4Flag
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void ClearInterrupt4Flag( void );
        
        //************************************
        // Method:    ClearInterrupt5Flag
        // FullName:  hal::PinInterrupt::ClearInterrupt5Flag
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void ClearInterrupt5Flag( void );
        
        //************************************
        // Method:    ClearInterrupt6Flag
        // FullName:  hal::PinInterrupt::ClearInterrupt6Flag
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void ClearInterrupt6Flag( void );
        
        //************************************
        // Method:    ClearInterrupt7Flag
        // FullName:  hal::PinInterrupt::ClearInterrupt7Flag
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void ClearInterrupt7Flag( void );
        
        //************************************
        // Method:    __vector_1
        // FullName:  hal::__vector_1
        // Access:    public
        // Returns:   friend void
        // Qualifier: INT0
        // Parameter: void
        //************************************
        friend void __vector_1( void );
        
        //************************************
        // Method:    __vector_2
        // FullName:  hal::__vector_2
        // Access:    public
        // Returns:   friend void
        // Qualifier: INT1
        // Parameter: void
        //************************************
        friend void __vector_2( void );
        
        //************************************
        // Method:    __vector_3
        // FullName:  hal::__vector_3
        // Access:    public
        // Returns:   friend void
        // Qualifier: INT2
        // Parameter: void
        //************************************
        friend void __vector_3( void );
        
        //************************************
        // Method:    __vector_4
        // FullName:  hal::__vector_4
        // Access:    public
        // Returns:   friend void
        // Qualifier: INT3
        // Parameter: void
        //************************************
        friend void __vector_4( void );
        
        //************************************
        // Method:    __vector_5
        // FullName:  hal::__vector_5
        // Access:    public
        // Returns:   friend void
        // Qualifier: INT4
        // Parameter: void
        //************************************
        friend void __vector_5( void );
        
        //************************************
        // Method:    __vector_6
        // FullName:  hal::__vector_6
        // Access:    public
        // Returns:   friend void
        // Qualifier: INT5
        // Parameter: void
        //************************************
        friend void __vector_6( void );
        
        //************************************
        // Method:    __vector_7
        // FullName:  hal::__vector_7
        // Access:    public
        // Returns:   friend void
        // Qualifier: INT6
        // Parameter: void
        //************************************
        friend void __vector_7( void );
        
        //************************************
        // Method:    __vector_8
        // FullName:  hal::__vector_8
        // Access:    public
        // Returns:   friend void
        // Qualifier: INT7
        // Parameter: void
        //************************************
        friend void __vector_8( void );
    };
};

#endif /* PIN_INTERRUPT_H_ */