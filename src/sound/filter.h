#ifndef FILTER_H_
#define FILTER_H_

typedef struct {

    float stages[4];
    float cutoff;
} Filter;

void filter_init(Filter *filter);
float filter_cycle(Filter *filter, float input);
void filter_free(Filter *filter);

#endif