#include <math.h>
#include <stdio.h>

#include "../common.h"
#include "filter.h"

void filter_init(Filter *filter) {

    filter->frequency = 200.0f;
    filter->previous_input = 0.0f;
    filter->previous_output = 0.0f;
}

float filter_cycle(Filter *filter, float input) {
    
    float x = tanf(M_PI * filter->frequency / SAMPLE_RATE);
    float output = x * input + x * filter->previous_input - (x-1) * filter->previous_output;
    
    output /= (x+1);

    filter->previous_output = output;
    filter->previous_input = input;

    return output;
}