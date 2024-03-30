#ifndef INSTRUMENT_H_
#define INSTRUMENT_H_

#include "../common.h"

typedef struct {

    int type;
    Parameter parameters[16]; 
    int parameters_count;

    int follow_indices[4];
    float follow_values[4];
} Instrument;

void instrument_init(Instrument *instrument);
void instrument_set_type(Instrument *instrument);
void instrument_add_parameter(Instrument *instrument, Parameter parameter);
void instrument_free(Instrument *instrument);

#endif