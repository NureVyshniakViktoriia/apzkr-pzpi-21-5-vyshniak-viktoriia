


#ifndef _NTC_TEMP_MODULE_
#define _NTC_TEMP_MODULE_


//******************
// CLASS: NTC_TEMP_CLASS
//
// DESCRIPTION:
//   ##      ##    ##
//  #  #    #     #
//  #        #     #
//  #  #      #     #
//   ##     ##    ##
//
// CREATED: 12.01.2019, by MarkT
//
// FILE: NTC_TEMP_MODULE.h
//
// SENSOR: NTC sensor 10k (NCP18XH103 - 3380K)
//


#include "Arduino.h"

#ifndef ADC_RESOLUTION_10
#ifndef ADC_RESOLUTION_12
    #define ADC_RESOLUTION_10
#endif
#endif

class NTC_TEMP_CLASS
{
    private:
        int   adc_channel = 0;
        float Linear(int value);
    public:
        NTC_TEMP_CLASS();
        NTC_TEMP_CLASS(int adc_channel);
        float GetTemp();
};

#endif