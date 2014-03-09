#ifndef SENSOR_H
#define SENSOR_H

#include "../../hal/inc/adc.h"
#include "../../hal/inc/ds18b20.h"

namespace bll
{
    void FriendOnAdcResultReceived(unsigned int adcResult );
    
    class SensorType
    {
        public:
        typedef enum
        {
            Temperature,
            Humidity,
            OxygenLevel,
            Unknown
        } ESensorType;
    };
    
    class Sensor
    {
        private:
        
        static Sensor* _instance;
        
        hal::Adc* _adc;
        
        hal::Ds18b20* _ds1820;
        
        bool _isTemperatureConversionInProgress;
        
        volatile int _currentTemperature;
        
        // To take 32 measurements and take the average
        static const unsigned char MaximumHumidityCount = 32;                
        
        volatile unsigned char _humidityIndex;
        
        volatile unsigned int _humidityValues[MaximumHumidityCount];
        
        volatile int _currentHumidity;
        
        volatile int _currentOxygenLevel;
        
        volatile SensorType::ESensorType _currentSensor;
        
        //************************************
        // Method:    Sensor
        // FullName:  bll::Sensor::Sensor
        // Access:    private
        // Returns:
        // Qualifier:
        // Parameter: void
        //************************************
        Sensor( void );
        
        //************************************
        // Method:    GetTemperatureAsync
        // FullName:  bll::Sensor::GetTemperatureAsync
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void GetTemperatureAsync( void );
        
        //************************************
        // Method:    GetHumidityAsync
        // FullName:  bll::Sensor::GetHumidityAsync
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void GetHumidityAsync( void );
        
        //************************************
        // Method:    GetOxygenLevelAsync
        // FullName:  bll::Sensor::GetOxygenLevelAsync
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void GetOxygenLevelAsync( void );
        
        //************************************
        // Method:    OnAdcResultReceived
        // FullName:  bll::Sensor::OnAdcResultReceived
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned int adcResult
        //************************************
        void OnAdcResultReceived(unsigned int adcResult);
        
        public:
        
        //************************************
        // Method:    GetInstance
        // FullName:  bll::Sensor::GetInstance
        // Access:    public static
        // Returns:   Sensor*
        // Qualifier:
        // Parameter: void
        //************************************
        static Sensor* GetInstance( void );
        
        //************************************
        // Method:    GetTemperature
        // FullName:  bll::Sensor::GetTemperature
        // Access:    public
        // Returns:   int
        // Qualifier:
        // Parameter: void
        //************************************
        int GetTemperature( void );
        
        //************************************
        // Method:    GetHumidity
        // FullName:  bll::Sensor::GetHumidity
        // Access:    public
        // Returns:   int
        // Qualifier:
        // Parameter: void
        //************************************
        int GetHumidity( void );
        
        //************************************
        // Method:    GetOxygenLevel
        // FullName:  bll::Sensor::GetOxygenLevel
        // Access:    public
        // Returns:   int
        // Qualifier:
        // Parameter: void
        //************************************
        int GetOxygenLevel( void );
        
        unsigned int ConvertLm35Value( unsigned int adcValue );
        
        unsigned int ConvertHsm20gValue( unsigned int adcValue );
        
        //************************************
        // Method:    FriendOnAdcResultReceived
        // FullName:  bll::FriendOnAdcResultReceived
        // Access:    public
        // Returns:   friend void
        // Qualifier:
        // Parameter: unsigned int adcResult
        //************************************
        friend void FriendOnAdcResultReceived(unsigned int adcResult);
    };
};

#endif // SENSOR_H
