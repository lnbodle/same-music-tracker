#ifndef FILTER_H_
#define FILTER_H_

typedef struct
{

    float previous_output;
    float previous_input;
    float frequency;
} Filter;

void filter_init(Filter *filter);
float filter_cycle(Filter *filter, float input);

#endif