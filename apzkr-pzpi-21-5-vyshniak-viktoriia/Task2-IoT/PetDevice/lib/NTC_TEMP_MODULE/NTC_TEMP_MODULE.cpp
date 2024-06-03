#include "NTC_TEMP_MODULE.h"

#define K_TABLE_ELEMENT(field) ((float)(((float)TEMP_TABLE[field + 1] - (float)TEMP_TABLE[field]) / ((float) ADC_TABLE[field + 1] - (float) ADC_TABLE[field])))
#define B_TABLE_ELEMENT(field, kField) ((float)((float) TEMP_TABLE[field] - kField * (float) ADC_TABLE[field]))

// Table for NTC sensor 10k (NCP18XH103 - 3380K)
// 14/10 bits adc resolution
static int ADC_TABLE[] =
{
#ifdef ADC_RESOLUTION_12
    199,
    259,
    332,
    420,
    523,
    643,
    780,
    933,
    1100,
    1279,
    1466,
    1660,
    1855,
    2048,
    2236,
    2416,
    2586,
    2745,
    2892,
    3025,
    3147,
    3254,
    3349,
    3434,
    3509,
    3576,
    3634,
    3686,
    3732,
    3771,
    3806,
    3837,
    3865,
    3889,
#elif defined ADC_RESOLUTION_10
    50,
    65,
    83,
    105,
    131,
    161,
    195,
    233,
    275,
    320,
    367,
    415,
    464,
    512,
    559,
    604,
    647,
    686,
    723,
    757,
    787,
    814,
    837,
    859,
    878,
    894,
    909,
    922,
    933,
    943,
    952,
    960,
    966,
    972,
#endif
};

static int TEMP_TABLE[] =
{
    -40,
    -35,
    -30,
    -25,
    -20,
    -15,
    -10,
    -5,
    0,
    5,
    10,
    15,
    20,
    25,
    30,
    35,
    40,
    45,
    50,
    55,
    60,
    65,
    70,
    75,
    80,
    85,
    90,
    95,
    100,
    105,
    110,
    115,
    120,
    125,
};

NTC_TEMP_CLASS::NTC_TEMP_CLASS(int adc_channel)
{
    this->adc_channel = adc_channel;
}

float NTC_TEMP_CLASS::GetTemp()
{
    return Linear(analogRead(this->adc_channel));
}

float NTC_TEMP_CLASS::Linear(int value)
{
	uint8_t n = sizeof(TEMP_TABLE)/sizeof(TEMP_TABLE[0]);

	// value outside the table
	if (value <= ADC_TABLE[0])
    {
		return TEMP_TABLE[0];
    }
	else if (value >= ADC_TABLE[n-1])
    {
		return TEMP_TABLE[n-1];
    }

	// value equals one of point
	for (uint8_t i = 0; i < n-1; ++i)
    {
		if (value == ADC_TABLE[i])
        {
			return TEMP_TABLE[i];
        }
    }

	// value between points
	for (uint8_t i = 0; i < n-1; ++i)
    {
		if (value >= ADC_TABLE[i] && value <= ADC_TABLE[i + 1])
        {
            float K = K_TABLE_ELEMENT(i);
            float B = B_TABLE_ELEMENT(i, K);
			return K * (float) value + B;
        }
    }

	return 0;
}














