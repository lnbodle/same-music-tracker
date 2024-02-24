#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "osc.h"
#include "filter.h"
#include "adsr.h"

typedef struct
{
    float tick;
    Osc osc;
    Filter filter;
    Adsr adsr;
} Channel;

void channel_init(Channel *channel);
float channel_cycle(Channel *channel);
void channel_set_frequency(Channel *channel, float frequency);
void channel_gate_on(Channel *channel);
void channel_gate_off(Channel *channel);

#endif