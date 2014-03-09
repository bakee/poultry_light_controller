#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include "hal_utils.h"
#include "timer2.h"

namespace hal
{
    typedef struct
    {
        MC_PIN SEG_PIN_A;
        MC_PIN SEG_PIN_B;
        MC_PIN SEG_PIN_C;
        MC_PIN SEG_PIN_D;
        MC_PIN SEG_PIN_E;
        MC_PIN SEG_PIN_F;
        MC_PIN SEG_PIN_G;
        MC_PIN SEG_PIN_R; // The decimal point (R for Radix Point)
    } SEGMENT;
    
    class DisplayMode
    {
        public:
        typedef enum
        {
            Normal,
            Empty,
            Dashed
        } EDisplayMode;
    };
    
    void FriendOnTimer2Interrupt( void );

    class SevenSegment
    {
        private:
        
        static SevenSegment* _instance;

        static const unsigned char SEG_A = 0;
        
        static const unsigned char SEG_B = 1;
        
        static const unsigned char SEG_C = 2;
        
        static const unsigned char SEG_D = 3;
        
        static const unsigned char SEG_E = 4;
        
        static const unsigned char SEG_F = 5;
        
        static const unsigned char SEG_G = 6;
        
        static const unsigned char SEG_R = 7;
        
        static const bool IS_DELAY_ENABLED = false;
        
        static const unsigned char SEVEN_SEGMENT_DELAY_AMOUNT = 2;
        
        static const unsigned char SYMBOL_COUNT = 18; // 0-9, A-F, empty and dash(-)
        
        static const unsigned int DISPLAY_COUNT = 11;
        
        volatile unsigned char _currentDisplaySegment;
        
        unsigned char _segmentValues[DISPLAY_COUNT];
        
        MC_PIN _segments[8];
        
        MC_PIN _addresses[DISPLAY_COUNT];
        
        unsigned char _valueArray[SYMBOL_COUNT];
        
        DisplayMode::EDisplayMode _displayMode;
        
        //************************************
        // Method:    SevenSegment
        // FullName:  hal::SevenSegment::SevenSegment
        // Access:    private
        // Returns:
        // Qualifier:
        // Parameter: void
        //************************************
        SevenSegment( void );

        //************************************
        // Method:    RegisterSegmentPins
        // FullName:  hal::SevenSegment::RegisterSegmentPins
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: SEGMENT segment
        //************************************
        void RegisterSegmentPins(SEGMENT segment);
        
        //************************************
        // Method:    InitializeSevenSegment
        // FullName:  hal::SevenSegment::InitializeSevenSegment
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void InitializeSevenSegment( void );
        
        //************************************
        // Method:    DrawOnSegment
        // FullName:  hal::SevenSegment::DrawOnSegment
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char segmentNo
        // Parameter: unsigned char value
        //************************************
        void DrawOnSegment(unsigned char segmentNo, unsigned char value);
        
        //************************************
        // Method:    Show
        // FullName:  hal::SevenSegment::Show
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char segmentNo
        // Parameter: unsigned char value
        //************************************
        void Show(unsigned char segmentNo, unsigned char value);

        //************************************
        // Method:    ClearAllAddressBus
        // FullName:  hal::SevenSegment::ClearAllAddressBus
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void ClearAllAddressBus( void );
        
        //************************************
        // Method:    SetDataBus
        // FullName:  hal::SevenSegment::SetDataBus
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char value
        //************************************
        void SetDataBus(unsigned char value);
        
        //************************************
        // Method:    SetAddressBus
        // FullName:  hal::SevenSegment::SetAddressBus
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char segmentNo
        //************************************
        void SetAddressBus(unsigned char segmentNo);
        
        //************************************
        // Method:    OnTimer2Interrupt
        // FullName:  hal::SevenSegment::OnTimer2Interrupt
        // Access:    private
        // Returns:   void
        // Qualifier:
        // Parameter: void
        //************************************
        void OnTimer2Interrupt( void );

        public:
        
        //************************************
        // Method:    GetInstance
        // FullName:  hal::SevenSegment::GetInstance
        // Access:    public static
        // Returns:   SevenSegment*
        // Qualifier:
        // Parameter: void
        //************************************
        static SevenSegment* GetInstance( void );
        
        //************************************
        // Method:    SetDisplayValue
        // FullName:  hal::SevenSegment::SetDisplayValue
        // Access:    public
        // Returns:   void
        // Qualifier:
        // Parameter: unsigned char segmentNo
        // Parameter: unsigned char value
        //************************************
        void SetDisplayValue(unsigned char segmentNo, unsigned char value);
        
        void SetDisplayMode( DisplayMode::EDisplayMode displayMode );
        
        //************************************
        // Method:    FriendOnTimer2Interrupt
        // FullName:  hal::FriendOnTimer2Interrupt
        // Access:    public
        // Returns:   friend void
        // Qualifier:
        // Parameter: void
        //************************************
        friend void FriendOnTimer2Interrupt( void );
    };
};
#endif // SEVEN_SEGMENT_H