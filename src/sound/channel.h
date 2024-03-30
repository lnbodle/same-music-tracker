#ifndef CHANNEL_H_
#define CHANNEL_H_

#define CHANNEL_VOICE_NUMBER 8

#include "../common.h"
#include "../instrument/instrument.h"
#include "osc.h"
#include "envelope.h"
#include "filter.h"
#include "sampler.h"

typedef struct
{
    float tick;
    float volume;
    float frequency;
    float gate;

    Osc osc;
    Sampler sampler;
    Envelope envelopes[4];
    Filter filter;

    Instrument *instrument;
} Channel;

void channel_init(Channel *channel);
void channel_free(Channel *channel);
float channel_cycle(Channel *channel);
void channel_set_frequency(Channel *channel, float frequency);
void channel_set_volume(Channel *channel, float volume);
void channel_gate_on(Channel *channel);
void channel_gate_off(Channel *channel);
float channel_substractive_cycle(Channel *channel);
float channel_sampler_cycle(Channel *channel);
void channel_set_instrument(Channel *channel, Instrument *instrument);

#endif