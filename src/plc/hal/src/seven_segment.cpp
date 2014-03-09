#include "../inc/seven_segment.h"
#include <avr/io.h>
#include <util/delay.h>

namespace hal
{
    /*
    The following macro changes the function:

    SEVEN_SEGMENT_MACRO(segment, A, D, 0, 0);

    to

    segment.SEG_PIN_A.DDR = &DDRD;
    segment.SEG_PIN_A.PORT = &PORTD;
    segment.SEG_PIN_A.PinNo = 0;
    _segments[0] = segment.SEG_PIN_A;


    */

    #define SEVEN_SEGMENT_MACRO(x, y, z, m, n) \
    x.SEG_PIN_ ## y.DDR = &DDR ## z;\
    x.SEG_PIN_ ## y.PORT = &PORT ## z;\
    x.SEG_PIN_ ## y.PinNo = m;\
    _ ## x ## s[n] = x.SEG_PIN_ ## y

    /*
    The following macro changes the function:

    SEVEN_TEMP_SEGMENT_MACRO(tempSegment, E, 0, 3);

    to

    tempSegment.DDR = &DDRE;
    tempSegment.PORT = &PORTE;
    tempSegment.PinNo = 0;
    _addresses[3] = tempSegment;

    */

    #define SEVEN_TEMP_SEGMENT_MACRO(x, y, m, n) \
    x.DDR = &DDR ## y;\
    x.PORT = &PORT ## y;\
    x.PinNo = m;\
    _addresses[n] = x


    SevenSegment* SevenSegment::_instance = NULL;
    
    SevenSegment::SevenSegment()
    {
        _currentDisplaySegment = 0;
        
        _valueArray[0] = (1 << SEG_A | 1 << SEG_B | 1 << SEG_C | 1 << SEG_D | 1 << SEG_E | 1 << SEG_F | 0 << SEG_G); // 0
        _valueArray[1] = (0 << SEG_A | 1 << SEG_B | 1 << SEG_C | 0 << SEG_D | 0 << SEG_E | 0 << SEG_F | 0 << SEG_G); // 1
        _valueArray[2] = (1 << SEG_A | 1 << SEG_B | 0 << SEG_C | 1 << SEG_D | 1 << SEG_E | 0 << SEG_F | 1 << SEG_G); // 2
        _valueArray[3] = (1 << SEG_A | 1 << SEG_B | 1 << SEG_C | 1 << SEG_D | 0 << SEG_E | 0 << SEG_F | 1 << SEG_G); // 3
        _valueArray[4] = (0 << SEG_A | 1 << SEG_B | 1 << SEG_C | 0 << SEG_D | 0 << SEG_E | 1 << SEG_F | 1 << SEG_G); // 4
        _valueArray[5] = (1 << SEG_A | 0 << SEG_B | 1 << SEG_C | 1 << SEG_D | 0 << SEG_E | 1 << SEG_F | 1 << SEG_G); // 5
        _valueArray[6] = (1 << SEG_A | 0 << SEG_B | 1 << SEG_C | 1 << SEG_D | 1 << SEG_E | 1 << SEG_F | 1 << SEG_G); // 6
        _valueArray[7] = (1 << SEG_A | 1 << SEG_B | 1 << SEG_C | 0 << SEG_D | 0 << SEG_E | 1 << SEG_F | 0 << SEG_G); // 7
        _valueArray[8] = (1 << SEG_A | 1 << SEG_B | 1 << SEG_C | 1 << SEG_D | 1 << SEG_E | 1 << SEG_F | 1 << SEG_G); // 8
        _valueArray[9] = (1 << SEG_A | 1 << SEG_B | 1 << SEG_C | 1 << SEG_D | 0 << SEG_E | 1 << SEG_F | 1 << SEG_G); // 9
        _valueArray[10] = (1 << SEG_A | 1 << SEG_B | 1 << SEG_C | 0 << SEG_D | 1 << SEG_E | 1 << SEG_F | 1 << SEG_G); // A
        _valueArray[11] = (0 << SEG_A | 0 << SEG_B | 1 << SEG_C | 1 << SEG_D | 1 << SEG_E | 1 << SEG_F | 1 << SEG_G); // B
        _valueArray[12] = (1 << SEG_A | 0 << SEG_B | 0 << SEG_C | 1 << SEG_D | 1 << SEG_E | 1 << SEG_F | 0 << SEG_G); // C
        _valueArray[13] = (0 << SEG_A | 1 << SEG_B | 1 << SEG_C | 1 << SEG_D | 1 << SEG_E | 0 << SEG_F | 1 << SEG_G); // D
        _valueArray[14] = (1 << SEG_A | 0 << SEG_B | 0 << SEG_C | 1 << SEG_D | 1 << SEG_E | 1 << SEG_F | 1 << SEG_G); // E
        _valueArray[15] = (1 << SEG_A | 0 << SEG_B | 0 << SEG_C | 0 << SEG_D | 1 << SEG_E | 1 << SEG_F | 1 << SEG_G); // F
        _valueArray[16] = (0 << SEG_A | 0 << SEG_B | 0 << SEG_C | 0 << SEG_D | 0 << SEG_E | 0 << SEG_F | 0 << SEG_G); // blank
        _valueArray[17] = (0 << SEG_A | 0 << SEG_B | 0 << SEG_C | 0 << SEG_D | 0 << SEG_E | 0 << SEG_F | 1 << SEG_G); // dash(-)

        InitializeSevenSegment();
        
        Timer2* timer2 = Timer2::GetInstance();
        timer2->Configure(Timer2WaveFormGenerationMode::Ctc, Timer2CompareOutputMode::NormalPortOperation, Timer2Prescaller::DividedBy1024);
        timer2->SetCompareRegister(F_CPU / 660 / 1024); // make 660 Hz interrupt so that finally 60Hz (i.e. 660 / 11 segments) refresh rate can be achieved
        timer2->EnableCompareMatchInterrupt();
        timer2->SetCompareMatchInterruptHandler(FriendOnTimer2Interrupt);
        
        _displayMode = DisplayMode::Dashed;
    }
    
    //************************************
    // Method:    GetInstance
    // FullName:  hal::SevenSegment::GetInstance
    // Access:    public
    // Returns:   SevenSegment*
    // Qualifier:
    //************************************
    SevenSegment* SevenSegment::GetInstance()
    {
        if(_instance == NULL)
        {
            static SevenSegment object;
            _instance = &object;
        }
        
        return _instance;
    }

    //************************************
    // Method:    InitializeSevenSegment
    // FullName:  SevenSegment::InitializeSevenSegment
    // Access:    private
    // Returns:   void
    // Qualifier:
    //************************************
    void SevenSegment::InitializeSevenSegment()
    {
        SEGMENT segment;

        SEVEN_SEGMENT_MACRO(segment, A, D, 0, 0);
        SEVEN_SEGMENT_MACRO(segment, B, D, 2, 1);
        SEVEN_SEGMENT_MACRO(segment, C, D, 3, 2);
        SEVEN_SEGMENT_MACRO(segment, D, D, 6, 3);
        SEVEN_SEGMENT_MACRO(segment, E, D, 5, 4);
        SEVEN_SEGMENT_MACRO(segment, F, D, 1, 5);
        SEVEN_SEGMENT_MACRO(segment, G, D, 7, 6);
        SEVEN_SEGMENT_MACRO(segment, R, D, 4, 7);

        MC_PIN tempSegment;

        // Temperature segments
        SEVEN_TEMP_SEGMENT_MACRO(tempSegment, G, 2, 0);
        SEVEN_TEMP_SEGMENT_MACRO(tempSegment, A, 7, 1);
        SEVEN_TEMP_SEGMENT_MACRO(tempSegment, A, 6, 2);
        SEVEN_TEMP_SEGMENT_MACRO(tempSegment, A, 5, 3);
        
        // Humidity Segments
        SEVEN_TEMP_SEGMENT_MACRO(tempSegment, A, 4, 4);
        SEVEN_TEMP_SEGMENT_MACRO(tempSegment, A, 3, 5);
        SEVEN_TEMP_SEGMENT_MACRO(tempSegment, A, 2, 6);
        SEVEN_TEMP_SEGMENT_MACRO(tempSegment, A, 1, 7);
        
        // Timer Segments
        SEVEN_TEMP_SEGMENT_MACRO(tempSegment, A, 0, 8);
        SEVEN_TEMP_SEGMENT_MACRO(tempSegment, F, 7, 9);
        SEVEN_TEMP_SEGMENT_MACRO(tempSegment, F, 6, 10);

        //InitializeDDRs

        for (unsigned int i = 0; i < 8; ++i)
        {
            SET_MC_PIN_OUTPUT(_segments[i]);
        }

        for (unsigned int i = 0; i < DISPLAY_COUNT; ++i)
        {
            SET_MC_PIN_OUTPUT(_addresses[i]);
            _segmentValues[i] = 0;
        }
    }

    //************************************
    // Method:    RegisterSegmentPins
    // FullName:  SevenSegment::RegisterSegmentPins
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: SEGMENT segment
    //************************************
    void SevenSegment::RegisterSegmentPins(SEGMENT segment)
    {

    }

    //************************************
    // Method:    Show
    // FullName:  SevenSegment::Show
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: unsigned char segmentNo
    // Parameter: unsigned char value
    //************************************
    void SevenSegment::Show(unsigned char segmentNo, unsigned char value)
    {
        if((value & 0x0F) > 10 || segmentNo >= DISPLAY_COUNT)
        {
            return;
        }
        
        unsigned char segmentValue = _valueArray[value & 0x0F];
        
        if((value & 0xF0) != 0) // Is decimal point present
        {
            segmentValue |= 0x80; // Set the 7th bit, i.e. the decimal point of the seven segment display
        }

        DrawOnSegment(segmentNo, segmentValue);
    }

    //************************************
    // Method:    DrawOnSegment
    // FullName:  SevenSegment::DrawOnSegment
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: unsigned char segmentNo
    // Parameter: unsigned char value
    //************************************
    void SevenSegment::DrawOnSegment(unsigned char segmentNo, unsigned char value)
    {
        ClearAllAddressBus();
        switch(_displayMode)
        {
            case DisplayMode::Normal:
            SetDataBus(value);
            break;
            
            case DisplayMode::Empty:
            SetDataBus(_valueArray[16]);
            break;
            
            case DisplayMode::Dashed:
            SetDataBus(_valueArray[17]);
            break;
        }
        
        SetAddressBus(segmentNo);
        
        if (IS_DELAY_ENABLED)
        {
            _delay_ms(SEVEN_SEGMENT_DELAY_AMOUNT);
        }
    }

    //************************************
    // Method:    SetDataBus
    // FullName:  SevenSegment::SetDataBus
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: unsigned char value
    //************************************
    void SevenSegment::SetDataBus(unsigned char value)
    {
        for (unsigned char i = 0; i < 8; ++i)
        {
            if(value & (1 << i))
            {
                SET_MC_PIN_HIGH(_segments[i]);
            }
            else
            {
                SET_MC_PIN_LOW(_segments[i]);
            }
        }
    }

    //************************************
    // Method:    ClearAllAddressBus
    // FullName:  SevenSegment::ClearAllAddressBus
    // Access:    private
    // Returns:   void
    // Qualifier:
    //************************************
    void SevenSegment::ClearAllAddressBus()
    {
        for (unsigned char i = 0; i < DISPLAY_COUNT; ++i)
        {
            SET_MC_PIN_LOW(_addresses[i]);
        }
    }

    //************************************
    // Method:    SetAddressBus
    // FullName:  SevenSegment::SetAddressBus
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: unsigned char segmentNo
    //************************************
    void SevenSegment::SetAddressBus(unsigned char segmentNo)
    {
        SET_MC_PIN_HIGH(_addresses[segmentNo]);
    }
    
    //************************************
    // Method:    SetDisplayValue
    // FullName:  hal::SevenSegment::SetDisplayValue
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: unsigned char segmentNo
    // Parameter: unsigned char value
    //************************************
    void SevenSegment::SetDisplayValue(unsigned char segmentNo, unsigned char value)
    {
        _segmentValues[segmentNo] = value;
    }

    //************************************
    // Method:    OnTimer2Interrupt
    // FullName:  hal::SevenSegment::OnTimer2Interrupt
    // Access:    private
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void SevenSegment::OnTimer2Interrupt( void )
    {
        Show(_currentDisplaySegment, _segmentValues[_currentDisplaySegment]);
        _currentDisplaySegment++;
        if(_currentDisplaySegment >= DISPLAY_COUNT)
        {
            _currentDisplaySegment = 0;
        }
    }

    void SevenSegment::SetDisplayMode( DisplayMode::EDisplayMode displayMode )
    {
        _displayMode = displayMode;
    }
    
    //************************************
    // Method:    OnTimer2Interrupt
    // FullName:  hal::OnTimer2Interrupt
    // Access:    public
    // Returns:   void
    // Qualifier:
    //************************************
    void FriendOnTimer2Interrupt()
    {
        SevenSegment::_instance->OnTimer2Interrupt();
    }
};