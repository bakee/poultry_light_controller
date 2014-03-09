
/*
* adc.h
*
* Created: 1/6/2013 8:42:04 PM
*  Author: muhammad
*/


#ifndef ADC_H_
#define ADC_H_

#include "hal_utils.h"
namespace hal
{
    class AdcAutoTriggerSource
    {
        public:
        typedef enum
        {
            FreeRunningmode,
            AnalogComparator,
            ExternalInterruptRequest0,
            TimerCounter0CompareMatch,
            TimerCounter0Overflow,
            TimerCounter1CompareMatchB,
            TimerCounter1Overflow,
            TimerCounter1CaptureEvent
        } EAdcAutoTriggerSource;
    };
    
    class AdcVoltageReference
    {
        public:
        typedef enum
        {
            ArefPin,
            Avcc,
            Internal2_56
        } EAdcVoltageReference;
    };

    typedef void (*AdcConversionCompletedCallback)(unsigned int);

    class Adc
    {
        private:
        
        static Adc* _instance;
        
        bool _isLeftAdjustedResult;
        
        bool _isInterruptEnabled;
        
        AdcConversionCompletedCallback _conversionCompletedCallback;
        
        //************************************
        // Method:    Adc
        // FullName:  hal::Adc::Adc
        // Access:    private
        // Returns:
        // Qualifier:
        // Parameter: void
        //************************************
        Adc( void );
        
        //************************************
        // Method:    Vector21
        // FullName:  hal::Adc::Vector21
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Vector21( void );
        
        public:
        
        //************************************
        // Method:    GetInstance
        // FullName:  hal::Adc::GetInstance
        // Access:    public static
        // Returns:   Adc*
        // Qualifier:
        // Parameter: void
        //************************************
        static Adc* GetInstance( void );
        
        //************************************
        // Method:    Enable
        // FullName:  hal::Adc::Enable
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Enable( void );
        
        //************************************
        // Method:    Disable
        // FullName:  hal::Adc::Disable
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void Disable( void );
        
        //************************************
        // Method:    Configure
        // FullName:  hal::Adc::Configure
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: AdcVoltageReference::EAdcVoltageReference adcVoltageReference
        // Parameter: bool isLeftAdjustedResult
        // Parameter: bool isInterruptEnabled
        // Parameter: bool isAutoTriggerEnabled
        //************************************
        void Configure(AdcVoltageReference::EAdcVoltageReference adcVoltageReference, bool isLeftAdjustedResult, bool isInterruptEnabled, bool isAutoTriggerEnabled = false);
        
        //************************************
        // Method:    StartConversion
        // FullName:  hal::Adc::StartConversion
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char channelNumber
        //************************************
        void StartConversion(unsigned char channelNumber);
        
        //************************************
        // Method:    SetAdcChannel
        // FullName:  hal::Adc::SetAdcChannel
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char channelNumber
        //************************************
        void SetAdcChannel(unsigned char channelNumber);
        
        //************************************
        // Method:    SetAdcConversionCompletedCallback
        // FullName:  hal::Adc::SetAdcConversionCompletedCallback
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: AdcConversionCompletedCallback callback
        //************************************
        void SetAdcConversionCompletedCallback(AdcConversionCompletedCallback callback);
        
        //************************************
        // Method:    SetAutoTriggerSource
        // FullName:  hal::Adc::SetAutoTriggerSource
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: AdcAutoTriggerSource::EAdcAutoTriggerSource autoTriggerSource
        //************************************
        void SetAutoTriggerSource(AdcAutoTriggerSource::EAdcAutoTriggerSource autoTriggerSource);
        
        //************************************
        // Method:    __vector_21
        // FullName:  hal::__vector_21
        // Access:    public
        // Returns:   friend void
        // Qualifier:
        // Parameter: void
        //************************************
        friend void __vector_21( void );
    };
};

#endif /* ADC_H_ */