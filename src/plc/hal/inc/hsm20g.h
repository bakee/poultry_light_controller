/*
* hsm20g.h
*
* Created: 3/3/2013 10:10:20 AM
*  Author: muhammad
*/


#ifndef HSM20G_H_
#define HSM20G_H_

namespace hal
{
    class Hsm20g
    {
        public:
        static unsigned int ConvertToRelativeHumidity(unsigned int adcCount);
    };
};


#endif /* HSM20G_H_ */