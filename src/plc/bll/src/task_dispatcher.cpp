/*
* task_dispatcher.cpp
*
* Created: 1/27/2013 11:45:34 PM
*  Author: muhammad
*/

#include "../inc/task_dispatcher.h"
#include "../../hal/inc/timer0.h"

//#define TIMER0_INTERRUPT_RATE 1
//#define TIMER0_INTERRUPT_RATE 2
//#define TIMER0_INTERRUPT_RATE 4
#define TIMER0_INTERRUPT_RATE 16
//#define TIMER0_INTERRUPT_RATE 128

namespace bll
{
    using namespace hal;
    
    TaskDispatcher* TaskDispatcher::_instance = NULL;
    
    TaskDispatcher::TaskDispatcher( void )
    {
        Timer0* t0 = Timer0::GetInstance();
#if (TIMER0_INTERRUPT_RATE == 1)
        t0->Configure(Timer0WaveFormGenerationMode::Normal, Timer0CompareOutputMode::NormalPortOperation, Timer0Prescaller::DividedBy128, true);
#elif (TIMER0_INTERRUPT_RATE == 2)
        t0->Configure(Timer0WaveFormGenerationMode::Normal, Timer0CompareOutputMode::NormalPortOperation, Timer0Prescaller::DividedBy64, true);
#elif (TIMER0_INTERRUPT_RATE == 4)
        t0->Configure(Timer0WaveFormGenerationMode::Normal, Timer0CompareOutputMode::NormalPortOperation, Timer0Prescaller::DividedBy32, true);
#elif (TIMER0_INTERRUPT_RATE == 16)
        t0->Configure(Timer0WaveFormGenerationMode::Normal, Timer0CompareOutputMode::NormalPortOperation, Timer0Prescaller::DividedBy8, true);
#elif (TIMER0_INTERRUPT_RATE == 128)
        t0->Configure(Timer0WaveFormGenerationMode::Normal, Timer0CompareOutputMode::NormalPortOperation, Timer0Prescaller::DividedBy1, true);
#endif
        t0->EnableOverflowInterrupt();
        t0->SetOverflowInterruptHandler(OnTimer0OverflowInterrupt);
        
        _availableTasks = 0;
        for (int i = 0; i < NumberOfTask; ++i)
        {
            _tasks[i] = NULL;
        }
    }

    TaskDispatcher* TaskDispatcher::GetInstance( void )
    {
        if(_instance == NULL)
        {
            static TaskDispatcher object;
            _instance = &object;
        }
        
        return _instance;
    }

    void TaskDispatcher::AddTask( Task task )
    {
        if( _availableTasks < NumberOfTask )
        {
            _tasks[_availableTasks] = task;
            _availableTasks++;
        }
    }

    void TaskDispatcher::DispatchTasks( void )
    {
        for (int i = 0; i < _availableTasks; ++i)
        {
            _tasks[i]();
        }
    }

    unsigned char TaskDispatcher::GetInterruptRate( void )
    {
        return TIMER0_INTERRUPT_RATE;
    }

    void OnTimer0OverflowInterrupt( void )
    {
        TaskDispatcher::_instance->DispatchTasks();
    }

};