#include "../inc/sensor.h"
#include "../../hal/inc/hsm20g.h"
using namespace hal;

namespace bll
{
    Sensor* Sensor::_instance = NULL;
    
    //************************************
    // Method:    Sensor
    // FullName:  bll::Sensor::Sensor
    // Access:    private
    // Returns:
    // Qualifier:
    //************************************
    Sensor::Sensor()
    {
        _currentTemperature = 0;
        
        _humidityIndex = 0;
        
        for (unsigned char i = 0; MaximumHumidityCount > i; ++i)
        {
            _humidityValues[i] = 0;
        }
        
        _currentHumidity = 0;
        _currentOxygenLevel = 0;
        _currentSensor = SensorType::Temperature;
        
        _adc = Adc::GetInstance();
        _adc->Enable();
        _adc->Configure(AdcVoltageReference::Avcc, false, true, true);
        _adc->SetAdcChannel(1);
        _adc->SetAutoTriggerSource(AdcAutoTriggerSource::TimerCounter0Overflow);
        _adc->SetAdcConversionCompletedCallback(FriendOnAdcResultReceived);
        
        _ds1820 = Ds18b20::GetInstance();
        _isTemperatureConversionInProgress = false;
    }
    
    //************************************
    // Method:    GetInstance
    // FullName:  bll::Sensor::GetInstance
    // Access:    public static
    // Returns:   Sensor*
    // Qualifier:
    //************************************
    Sensor* Sensor::GetInstance()
    {
        if (_instance == NULL)
        {
            static Sensor object;
            _instance = &object;
        }
        
        return _instance;
    }

    //************************************
    // Method:    GetTemperatureAsync
    // FullName:  bll::Sensor::GetTemperatureAsync
    // Access:    private
    // Returns:   void
    // Qualifier:
    //************************************
    void Sensor::GetTemperatureAsync()
    {
        _adc->StartConversion(0);
    }
    
    //************************************
    // Method:    GetHumidityAsync
    // FullName:  bll::Sensor::GetHumidityAsync
    // Access:    private
    // Returns:   void
    // Qualifier:
    //************************************
    void Sensor::GetHumidityAsync()
    {
        _adc->StartConversion(1);
    }
    
    //************************************
    // Method:    GetOxygenLevelAsync
    // FullName:  bll::Sensor::GetOxygenLevelAsync
    // Access:    private
    // Returns:   void
    // Qualifier:
    //************************************
    void Sensor::GetOxygenLevelAsync()
    {
        _adc->StartConversion(2);
    }
    
    //************************************
    // Method:    GetTemperature
    // FullName:  bll::Sensor::GetTemperature
    // Access:    public
    // Returns:   int
    // Qualifier:
    //************************************
    int Sensor::GetTemperature()
    {
        if (_isTemperatureConversionInProgress)
        {
            if (_ds1820->IsConversionCompleted())
            {
                _isTemperatureConversionInProgress = false;
                unsigned int temperature = _ds1820->GetTemperatureValue();
                if(temperature > 0)
                {
                    // For Celcius
                    //_currentTemperature = temperature;
                    
                    // For Fahrenheit
                    _currentTemperature = (temperature * 9 + 1600) / 5;
                }
            }
        }
        else
        {
            _ds1820->StartConversion();
            _isTemperatureConversionInProgress = true;
        }
        
        return _currentTemperature;
    }
    
    //************************************
    // Method:    GetHumidity
    // FullName:  bll::Sensor::GetHumidity
    // Access:    public
    // Returns:   int
    // Qualifier:
    //************************************
    int Sensor::GetHumidity()
    {
        return _currentHumidity + 50; // Since in practical the humidity value is 5 less than the actual value, so 50 (i.e. 5.0%RH) is added as a patch
    }
    
    //************************************
    // Method:    GetOxygenLevel
    // FullName:  bll::Sensor::GetOxygenLevel
    // Access:    public
    // Returns:   int
    // Qualifier:
    //************************************
    int Sensor::GetOxygenLevel()
    {
        return _currentOxygenLevel;
    }

    //************************************
    // Method:    OnAdcResultReceived
    // FullName:  bll::Sensor::OnAdcResultReceived
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: unsigned int adcResult
    //************************************
    void Sensor::OnAdcResultReceived( unsigned int adcResult )
    {
        // Only Humidity Sensor is enabled and is connected to ADC channel 1
        
        unsigned int total = 0;
        
        _humidityValues[_humidityIndex++] = ConvertHsm20gValue( adcResult );
        
        for(unsigned char i = 0; i < MaximumHumidityCount; ++i)
        {
            total += _humidityValues[i];
        }
        
        _currentHumidity = total / MaximumHumidityCount;
        
        if(MaximumHumidityCount <= _humidityIndex)
        {
            _humidityIndex = 0;
        }
    }

    //************************************
    // Method:    ConvertHsm20gValue
    // FullName:  bll::Sensor::ConvertHsm20gValue
    // Access:    public
    // Returns:   int
    // Qualifier: Converts to 10 x humidity from ADC count
    // Parameter: int adcValue
    //************************************
    unsigned int Sensor::ConvertHsm20gValue( unsigned int adcValue )
    {
        return Hsm20g::ConvertToRelativeHumidity(adcValue);
    }

    //************************************
    // Method:    ConvertLm35Value
    // FullName:  bll::Sensor::ConvertLm35Value
    // Access:    public
    // Returns:   int
    // Qualifier: Converts to 10 x temperature from ADC count
    // Parameter: int adcValue
    //************************************
    unsigned int Sensor::ConvertLm35Value( unsigned int adcValue )
    {
        unsigned long temp = adcValue;
        temp *= 5000;
        return temp / 1024 ; // This equation is valid when ADC reference AVCC
    }

    //************************************
    // Method:    FriendOnAdcResultReceived
    // FullName:  bll::FriendOnAdcResultReceived
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: unsigned int adcResult
    //************************************
    void FriendOnAdcResultReceived(unsigned int adcResult )
    {
        Sensor::_instance->OnAdcResultReceived(adcResult);
    }
};