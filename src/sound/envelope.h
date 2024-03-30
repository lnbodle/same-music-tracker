#ifndef ENVELOPE_H_
#define ENVELOPE_H_

#include "adsr.h"

typedef enum {
    ENVELOPE_ADSR,
    ENVELOPE_LFO
} EnvelopeTypes;

typedef struct {

    int type;
    float parameters[4];
    
    Adsr adsr;
    float gate;

} Envelope;

void envelope_init(Envelope *envelope);
float envelope_cycle(Envelope *envelope);
float envelope_gate_on(Envelope *envelope);
float envelope_gate_reset(Envelope *envelope);

#endif