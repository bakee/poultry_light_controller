#ifndef SYSTEM_TIME_H_
#define SYSTEM_TIME_H_

#include "../../hal/inc/hal_utils.h"

namespace bll
{
void FriendUpdateTime( void );
class SystemTime{

private:

	SystemTime(void);

	static SystemTime* _instance;

	int _hour;
	int _displayHour;
	int _minute;
	int _second;
	char _amPmChar;

	void UpdateTime( void );

public:

	static SystemTime* GetInstance( void );

	int GetHour(void);

	int GetMinute(void);

	int GetSecond(void);

	int GetAmPmChar(void);

	friend void FriendUpdateTime( void );
};
};


#endif
