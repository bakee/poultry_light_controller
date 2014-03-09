/*
* hsm20g.cpp
*
* Created: 3/3/2013 10:10:33 AM
*  Author: muhammad
*/

#include "../inc/hsm20g.h"

namespace hal
{
    /*
    *   From HSM20G Datasheet:
    *
    *   +---------+------+------+------+------+------+------+------+------+------+
    *   |   %RH   |  10  |  20  |  30  |  40  |  50  |  60  |  70  |  80  |  90  |
    *   |---------+------+------+------+------+------+------+------+------+------|
    *   | OutputV | 0.74 | 0.95 | 1.31 | 1.68 | 2.02 | 2.37 | 2.69 | 2.99 | 3.19 |
    *   +---------+------+------+------+------+------+------+------+------+------+
    */

    static const unsigned int _adcCountValues[] = {151, 194, 268, 344, 413, 485, 550, 612, 653};


    unsigned int Hsm20g::ConvertToRelativeHumidity( unsigned int adcCount )
    {
        //return ( 17 * adcValue - 1859 ) / 10; // This equation is valid when ADC reference AVCC
    
        unsigned char i = 0;
        for(; 9 > i; ++i)
        {
            if(adcCount <= _adcCountValues[i])
            {
                break;
            }
        }
    
        if(adcCount == _adcCountValues[i])
        {
            return (i + 1) * 100;
        }
        else if(i == 9)
        {
            // Greater than 90% RH
            return 910; // 91.0%
        }
        else if(i == 0)
        {
            // Less than 10% RH
            return 90; // 9.0%
        }
        else
        {
            unsigned int lowerValue = _adcCountValues[i - 1];
            unsigned int upperValue = _adcCountValues[i];
            return (i * 100) + ((adcCount - lowerValue) * 100) / (upperValue - lowerValue);
        }
    }
};