/*
* adc.cpp
*
* Created: 1/6/2013 9:45:29 PM
*  Author: muhammad
*/
#include "../inc/adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>

namespace hal
{
    Adc* Adc::_instance = NULL;
    
    //************************************
    // Method:    Adc
    // FullName:  hal::Adc::Adc
    // Access:    public
    // Returns:
    // Qualifier:
    //************************************
    Adc::Adc()
    {
        _isLeftAdjustedResult = false;
        _isInterruptEnabled = false;
        _conversionCompletedCallback = NULL;
    }
    
    //************************************
    // Method:    GetInstance
    // FullName:  hal::Adc::GetInstance
    // Access:    public static
    // Returns:   Adc*
    // Qualifier:
    //************************************
    Adc* Adc::GetInstance()
    {
        if (_instance == NULL)
        {
            static Adc object;
            _instance = &object;
        }
        
        return _instance;
    }
    
    //************************************
    // Method:    Enable
    // FullName:  hal::Adc::Enable
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Adc::Enable( void )
    {
        ADCSRA |= (1 << ADEN);
    }

    //************************************
    // Method:    Disable
    // FullName:  hal::Adc::Disable
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Adc::Disable( void )
    {
        ADCSRA &= ~(1 << ADEN);
    }

    //************************************
    // Method:    Configure
    // FullName:  hal::Adc::Configure
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: AdcVoltageReference adcVoltageReference
    // Parameter: bool isLeftAdjustedResult
    // Parameter: bool isInterruptEnabled
    //************************************
    void Adc::Configure( AdcVoltageReference::EAdcVoltageReference adcVoltageReference, bool isLeftAdjustedResult, bool isInterruptEnabled, bool isAutoTriggerEnabled )
    {
        _isInterruptEnabled = isInterruptEnabled;
        _isLeftAdjustedResult = isLeftAdjustedResult;
        
        unsigned char admux = ADMUX & ((0 << REFS1) | (0 << REFS0) | (0 << ADLAR) | (1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
        unsigned char adcsra = ADCSRA & ((1 << ADEN) | (1 << ADSC ) | (0 << ADATE) | (1 << ADIF) | (0 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
        
        switch(adcVoltageReference)
        {
            case AdcVoltageReference::Avcc:
            admux |= (1 << REFS0);
            break;
            
            case AdcVoltageReference::Internal2_56:
            admux |= ((1 << REFS1) | (1 << REFS0));
            break;
            
            case AdcVoltageReference::ArefPin:
            default:
            break;
        }
        
        if (isLeftAdjustedResult)
        {
            admux |= (1 << ADLAR);
        }       
        
        if (isInterruptEnabled)
        {
            adcsra |= (1 << ADIE);
        }
        
        if (isAutoTriggerEnabled)
        {
            adcsra |= (1 << ADATE);
        }
        
        // Pre-scaler is always 128 i.e. for 16 MHz system clock, ADC clock rate is 125 kHz
        // and for 8MHz system clock it is 62.5 kHz
        adcsra |= ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));        
        
        ADMUX = admux;
        ADCSRA = adcsra;
    }

    //************************************
    // Method:    StartConversion
    // FullName:  hal::Adc::StartConversion
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: int channelNumber
    //************************************
    void Adc::StartConversion(unsigned char channelNumber )
    {
        ADMUX = ((ADMUX & 0xE0) | channelNumber);
        
        // Start the conversion and clear the interrupt flag
        ADCSRA |= ((1 << ADSC) | (1 << ADIF));
        
        if(!_isInterruptEnabled)
        {
            // Wait till the ADSC bit is set, i.e. the conversion is in progress
            while(ADCSRA & (1 << ADSC));
            
            // Forcefully clear the pending interrupt flag
            ADCSRA |= (1 << ADIF);
            
            if (_isLeftAdjustedResult)
            {
                _conversionCompletedCallback(ADCH);
            }
            else
            {
                _conversionCompletedCallback(ADC);
            }
        }
    }
    
    //************************************
    // Method:    SetAdcChannel
    // FullName:  hal::Adc::SetAdcChannel
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: unsigned char channelNumber
    //************************************
    void Adc::SetAdcChannel(unsigned char channelNumber)
    {
        ADMUX = ((ADMUX & 0xE0) | channelNumber);
    }

    //************************************
    // Method:    SetAdcConversionCompletedCallback
    // FullName:  hal::Adc::SetAdcConversionCompletedCallback
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: AdcConversionCompletedCallback callback
    //************************************
    void Adc::SetAdcConversionCompletedCallback( AdcConversionCompletedCallback callback )
    {
        _conversionCompletedCallback = callback;
    }

    //************************************
    // Method:    SetAutoTriggerSource
    // FullName:  hal::SetAutoTriggerSource
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: AdcAutoTriggerSource::EAdcAutoTriggerSource autoTriggerSource
    //************************************
    void Adc::SetAutoTriggerSource(AdcAutoTriggerSource::EAdcAutoTriggerSource autoTriggerSource)
    {
        unsigned char adcsrb = 0;
        
        switch (autoTriggerSource)
        {
            case AdcAutoTriggerSource::AnalogComparator:
            adcsrb = (1 << ADTS0);
            break;
            
            case AdcAutoTriggerSource::ExternalInterruptRequest0:
            adcsrb = (1 << ADTS1);
            break;
            
            case AdcAutoTriggerSource::TimerCounter0CompareMatch:
            adcsrb = (1 << ADTS1) | (1 << ADTS0);
            break;
            
            case AdcAutoTriggerSource::TimerCounter0Overflow:
            adcsrb = (1 << ADTS2);
            break;
            
            case AdcAutoTriggerSource::TimerCounter1CompareMatchB:
            adcsrb = (1 << ADTS2) | (1 << ADTS0);
            break;
            
            case AdcAutoTriggerSource::TimerCounter1Overflow:
            adcsrb = (1 << ADTS2) | (1 << ADTS1);
            break;
            
            case AdcAutoTriggerSource::TimerCounter1CaptureEvent:
            adcsrb = (1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0);
            break;
            
            case AdcAutoTriggerSource::FreeRunningmode:
            default:
            break;
        }
        
        ADCSRB = adcsrb;
    }

    //************************************
    // Method:    Vector21
    // FullName:  hal::Adc::Vector21
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void Adc::Vector21( void )
    {
        if (_isLeftAdjustedResult)
        {
            _conversionCompletedCallback(ADCH);
        }
        else
        {
            _conversionCompletedCallback(ADC);
        }
    }
    
    //************************************
    // Method:    __vector_21
    // FullName:  hal::__vector_21
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void __vector_21( void )
    {
        Adc::_instance->Vector21();
    }
};