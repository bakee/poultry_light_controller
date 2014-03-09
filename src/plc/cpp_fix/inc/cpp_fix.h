/*
* cpp_fix.h
*
* Created: 1/15/2013 12:37:43 AM
*  Author: muhammad
*/


#ifndef CPP_FIX_H_
#define CPP_FIX_H_

#include <stdlib.h>

void * operator new(size_t size);
void operator delete(void * ptr);

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);


extern "C" void __cxa_pure_virtual( void );



#endif /* CPP_FIX_H_ */