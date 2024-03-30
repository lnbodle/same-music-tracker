
#include <math.h>
#include "../common.h"
#include "filter.h"

void filter_init(Filter *filter)
{
    filter->cutoff = 1000.0f;
}

float filter_cycle(Filter *filter, float input)
{

    float delta_time = 1.0f / (float)SAMPLE_RATE;

    float fc = filter->cutoff;
    float rc = 1.0f / (2 * M_PI * fc);
    float dt = delta_time;
    float a = dt / (rc + dt);

    filter->stages[0] = a * input + (1.0f - a) * filter->stages[0];
    for (int i = 0; i < 4; i++)
    {
        filter->stages[i] = a * filter->stages[i - 1] + (1.0f - a) * filter->stages[i];
    }

    return filter->stages[3];
}

void filter_free(Filter *filter)
{
}