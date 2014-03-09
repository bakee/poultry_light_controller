/*
* task_dispatcher.h
*
* Created: 1/27/2013 11:44:09 PM
*  Author: muhammad
*/


#ifndef TASK_DISPATCHER_H_
#define TASK_DISPATCHER_H_

namespace bll
{
    typedef void (*Task) ( void );
    void OnTimer0OverflowInterrupt( void );
    class TaskDispatcher
    {
        private:
        TaskDispatcher( void );
        static TaskDispatcher* _instance;
        static const unsigned char NumberOfTask = 8;
        Task _tasks[NumberOfTask];
        unsigned char _availableTasks;
        
        void DispatchTasks( void );
        
        public:
        static TaskDispatcher* GetInstance( void );
        static unsigned char GetInterruptRate( void );
        void AddTask( Task task );
        friend void OnTimer0OverflowInterrupt( void );
    };
};

#endif /* TASK_DISPATCHER_H_ */