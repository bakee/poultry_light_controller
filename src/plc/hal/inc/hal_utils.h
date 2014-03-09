#ifndef HAL_UTILS_H
#define HAL_UTILS_H

#include <avr/interrupt.h>

#ifndef NULL
#define NULL 0
#endif


#define SET_MC_PIN_OUTPUT(pin) *(pin.DDR) |= (1 << pin.PinNo)
#define SET_MC_PIN_INPUT(pin) *(pin.DDR) &= ~(1 << pin.PinNo)
#define SET_MC_PIN_HIGH(pin) *(pin.PORT) |= (1 << pin.PinNo)
#define SET_MC_PIN_LOW(pin) *(pin.PORT) &= ~(1 << pin.PinNo)
#define IS_MC_PIN_HIGH(pin) ((((*(pin.PIN)) >> pin.PinNo) & 0x01) == 0x01)
#define IS_MC_PIN_LOW(pin) ((((*(pin.PIN)) >> pin.PinNo) & 0x01) == 0x00)


namespace hal
{
    typedef struct
    {
        volatile unsigned char* DDR;
        volatile unsigned char* PORT;
        volatile unsigned char* PIN;
        unsigned char PinNo;
    } MC_PIN;
    
    typedef void (*InterruptHandler)( void );
    
    extern "C"
    {
        void __vector_1( void ) __attribute__ ((signal));  // INT0
        void __vector_2( void ) __attribute__ ((signal));  // INT1
        void __vector_3( void ) __attribute__ ((signal));  // INT2
        void __vector_4( void ) __attribute__ ((signal));  // INT3
        void __vector_5( void ) __attribute__ ((signal));  // INT4
        void __vector_6( void ) __attribute__ ((signal));  // INT5
        void __vector_7( void ) __attribute__ ((signal));  // INT6
        void __vector_8( void ) __attribute__ ((signal));  // INT7
        void __vector_9( void ) __attribute__ ((signal));  // Timer/Counter2 CompareMatch
        void __vector_10( void ) __attribute__ ((signal)); // Timer/Counter2 Overflow
        void __vector_11( void ) __attribute__ ((signal)); // Timer/Counter1 Capture Event
        void __vector_12( void ) __attribute__ ((signal)); // Timer/Counter1 Compare Match A
        void __vector_13( void ) __attribute__ ((signal)); // Timer/Counter1 Compare Match B
        void __vector_14( void ) __attribute__ ((signal)); // Timer/Counter1 Overflow
        void __vector_15( void ) __attribute__ ((signal)); // Timer/Counter0 Compare Match
        void __vector_16( void ) __attribute__ ((signal)); // Timer/Conter0 Overflow
        void __vector_17( void ) __attribute__ ((signal)); // SPI Serial Transfer Complete
        void __vector_18( void ) __attribute__ ((signal)); // USART0, Rx Complete
        void __vector_19( void ) __attribute__ ((signal)); // USART0 Data Register Empty
        void __vector_20( void ) __attribute__ ((signal)); // USART0, Tx Complete
        void __vector_21( void ) __attribute__ ((signal)); // ADC Conversion Complete
        void __vector_22( void ) __attribute__ ((signal)); // EEPROM Ready
        void __vector_23( void ) __attribute__ ((signal)); // Analog Comparator
        void __vector_24( void ) __attribute__ ((signal)); // Timer/Countre1 Compare Match C
        void __vector_25( void ) __attribute__ ((signal)); // Timer/Counter3 Capture Event
        void __vector_26( void ) __attribute__ ((signal)); // Timer/Counter3 Compare Match A
        void __vector_27( void ) __attribute__ ((signal)); // Timer/Counter3 Compare Match B
        void __vector_28( void ) __attribute__ ((signal));	// Timer/Counter3 Compare Match C
        void __vector_29( void ) __attribute__ ((signal));	// Timer/Counter3 Overflow
        void __vector_30( void ) __attribute__ ((signal));	// USART1, Rx Complete
        void __vector_31( void ) __attribute__ ((signal));	// USART1 Data Register Empty
        void __vector_32( void ) __attribute__ ((signal));	// USART1, Tx Complete
        void __vector_33( void ) __attribute__ ((signal));	// Two-wire Serial Interface
        void __vector_34( void ) __attribute__ ((signal));	// Store Program Memory Ready
    }
};


#endif // HAL_UTILS_H
