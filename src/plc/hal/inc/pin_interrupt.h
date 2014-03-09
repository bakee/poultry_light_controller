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
        
        PinInterrupt( void );
        
        void HandleDebounce( void );
        
        void Vector1( void );
        
        void Vector2( void );
        
        void Vector3( void );
        
        void Vector4( void );
        
        void Vector5( void );
        
        void Vector6( void );
        
        void Vector7( void );
        
        void Vector8( void );
        
        public:
        
        static PinInterrupt* GetInstance( void );
        
        void SetInterrupt0Handler(InterruptHandler handler);
        
        void SetInterrupt1Handler(InterruptHandler handler);
        
        void SetInterrupt2Handler(InterruptHandler handler);
        
        void SetInterrupt3Handler(InterruptHandler handler);
        
        void SetInterrupt4Handler(InterruptHandler handler);
        
        void SetInterrupt5Handler(InterruptHandler handler);

        void SetInterrupt5ReleasedHandler(InterruptHandler handler);        
        
        void SetInterrupt6Handler(InterruptHandler handler);

        void SetInterrupt6ReleasedHandler(InterruptHandler handler);        
        
        void SetInterrupt7Handler(InterruptHandler handler);
        
        void SetInterrupt0Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        void SetInterrupt1Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        void SetInterrupt2Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        void SetInterrupt3Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        void SetInterrupt4Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        void SetInterrupt5Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        void SetInterrupt6Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        void SetInterrupt7Mode(InterruptSenseControl::EInterruptSenseControl interruptMode);
        
        void EnableInterrupt0( void );
        
        void EnableInterrupt1( void );
        
        void EnableInterrupt2( void );
        
        void EnableInterrupt3( void );
        
        void EnableInterrupt4( void );
        
        void EnableInterrupt5( void );
        
        void EnableInterrupt6( void );
        
        void EnableInterrupt7( void );
        
        void DisableInterrupt0( void );
        
        void DisableInterrupt1( void );
        
        void DisableInterrupt2( void );
        
        void DisableInterrupt3( void );
        
        void DisableInterrupt4( void );
        
        void DisableInterrupt5( void );
        
        void DisableInterrupt6( void );
        
        void DisableInterrupt7( void );
        
        void ClearInterrupt0Flag( void );
        
        void ClearInterrupt1Flag( void );
        
        void ClearInterrupt2Flag( void );
        
        void ClearInterrupt3Flag( void );
        
        void ClearInterrupt4Flag( void );
        
        void ClearInterrupt5Flag( void );
        
        void ClearInterrupt6Flag( void );
        
        void ClearInterrupt7Flag( void );
        
        friend void __vector_1( void );
        
        friend void __vector_2( void );
        
        friend void __vector_3( void );
        
        friend void __vector_4( void );
        
        friend void __vector_5( void );
        
        friend void __vector_6( void );
        
        friend void __vector_7( void );
        
        friend void __vector_8( void );
    };
};

#endif