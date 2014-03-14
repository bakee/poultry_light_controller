#ifndef TIME_SETTINGS_H_
#define TIME_SETTINGS_H_

typedef struct
{
	unsigned totalMinutes : 12;
	unsigned displayHour : 4;
	unsigned displayMinute : 6;
	unsigned isDisplayTimeInPm : 2;
} RelayTime;

#endif
