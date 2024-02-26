#include "channel.h"
#include "adsr.h"
#include "filter.h"
#include "osc.h"
#include "../utils.h"

void channel_init(Channel *channel)
{

    instrument_init(&channel->instruments[0]);
    filter_init(&channel->filter);
    adsr_init(&channel->adsr);
}

float channel_cycle(Channel *channel)
{

    float adsr = adsr_cycle(&channel->adsr) * channel->volume;
    return instrument_cycle(&channel->instruments[0]) * adsr;
}

void channel_set_volume(Channel *channel, float volume) {

    channel->volume = volume;
}

void channel_set_frequency(Channel *channel, float frequency)
{
    channel->instruments[0].frequency = frequency;
}

void channel_gate_on(Channel *channel)
{

    adsr_gate(&channel->adsr);
}

void channel_gate_off(Channel *channel)
{

    adsr_reset(&channel->adsr);
}