#include "../../hal/inc/eeprom.h"
#include "../inc/relay_settings.h"
#include "../inc/menu.h"
#include "../inc/relay_manager.h"

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#define DEFAULT_TEMP_INC_DEC_VALUE 1
#define TEMP_RELAY_2_INTERVAL_INC_DEC_VALUE 1
#define TEMP_RELAY_3_INTERVAL_INC_DEC_VALUE 1
#define DEFAULT_HUM_INC_DEC_VALUE 1
#define TIMER_1_RELAY_INTERVAL_INC_DEC_VALUE 1
#define TIMER_2_RELAY_INTERVAL_INC_DEC_VALUE 1
#define TIMER_2_RELAY_TURN_ON_TIME_INC_DEC_VALUE 1
#define DEFAULT_OXYGEN_LEVEL_INC_DEC_VALUE 1

namespace bll
{
    class IncreaseDecreaseType
    {
        public:
        typedef enum
        {
            Normal,
            Fast,
            Faster
        } EIncreaseDecreaseType;
    };
    
    void FriendDecrementConfigurationTimeout( void );
    
    class Configuration;
    typedef void (Configuration::*ButtonHandler) ( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
    
    class Configuration
    {
        private:
        
        static Configuration* _instance;
        
        Configuration( void );
        
        hal::Eeprom* _eeprom;
        
        Menu* _menu;
        
        RelayManager* _relayManager;
        
        volatile unsigned char _menuTimeout;
        
        volatile unsigned char _autoStartTimeOutValue;
        
        RelaySettings _relaySettings; // To store default settings
        
        RelaySettings _temporaryRelaySettings; // To store temporary settings
        
        ButtonHandler _onIncrease;
        
        ButtonHandler _onDecrease;
        
        static const unsigned char NumberOfState = 5;
        
        ButtonHandler _increaseHandler[NumberOfState];
        
        ButtonHandler _decreaseHandler[NumberOfState];
        
        unsigned char _state;
        
        static const unsigned char MenuTimeoutValue = 15; // 15 1Hz pulse, i.e. 15 seconds
        
        void SetToDefaultState( void );
        
        void RefreshMenuTimeout( void );
        
        void GetDefaultValues( void );
        
        bool ReadDefaultValuesFromEeprom( void );
        
        void WriteDefaultValuesToEeprom( void );
        
        void DecrementConfigurationTimeout( void );
	void FormatDisplayTime(int number);
	unsigned char GetIncrementAmount(
			IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType);

        public:
        
        static Configuration* GetInstance( void );
        
        void IncreaseValue( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void SetIncreaseHandler( ButtonHandler increaseHandler );
        
        void DecreaseValue( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );

        void SetDecreaseHandler( ButtonHandler decreaseHandler );
        
        void IncreaseTimeValue(IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType, int number);

        void DecreaseTimeValue(IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType, int number);

        void IncreaseStartTime1Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void IncreaseEndTime1Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );

        void IncreaseStartTime2Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void IncreaseEndTime2Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );

        void IncreaseTemperatureRelay3Interval( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void IncreaseDefaultHumidity( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void IncreaseTimer1RelayInterval( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void IncreaseTimer2RelayInterval( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void IncreaseTimer2TurnOntime( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void IncreaseDefaultOxygenLevel( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void SaveChanges( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void DiscardChanges( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void DecreaseStartTime1Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void DecreaseEndTime1Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void DecreaseStartTime2Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void DecreaseEndTime2Value( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void DecreaseTimer1RelayInterval( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void DecreaseTimer2RelayInterval( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void DecreaseTimer2TurnOntime( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void DecreaseDefaultOxygenLevel( IncreaseDecreaseType::EIncreaseDecreaseType increaseDecreaseType );
        
        void SetNextEventHandler( void );
        
        void SetPreviousEventHandler( void );
        
        unsigned char GetState( void )
        {
            return _state;
        }
        
        friend void FriendDecrementConfigurationTimeout( void );
    };
};

#endif
