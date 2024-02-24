#include "channel.h"
#include "adsr.h"
#include "filter.h"
#include "osc.h"

void channel_init(Channel *channel)
{

    osc_init(&channel->osc);
    filter_init(&channel->filter);
    adsr_init(&channel->adsr);
}

float channel_cycle(Channel *channel)
{

    float adsr = adsr_cycle(&channel->adsr);

    channel->filter.frequency = 100 + adsr * 3000;

    return filter_cycle(&channel->filter, osc_cycle(&channel->osc)) * adsr;
    
}

void channel_set_frequency(Channel *channel, float frequency)
{

    channel->osc.frequency = frequency;
}

void channel_gate_on(Channel *channel)
{

    adsr_gate(&channel->adsr);
}

void channel_gate_off(Channel *channel)
{

    adsr_reset(&channel->adsr);
}