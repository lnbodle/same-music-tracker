#include "channel.h"
#include "../utils.h"
#include "../common.h"

void channel_init(Channel *channel)
{
    for (int i = 0; i < ENVELOPE_NUMBER; i++)
    {
        envelope_init(&channel->envelopes[i]);
    }

    filter_init(&channel->filter);
    channel->gate = 0;

    channel->instrument = 0;

    sampler_load_sample(&channel->sampler, "samples/test.wav");
}

void channel_free(Channel *channel)
{
    filter_free(&channel->filter);
}

float channel_cycle(Channel *channel)
{
    float out = 0;

    

    if (channel->instrument == 0)
        return 0;

    for (int i = 0 ; i < 16 ; i++) {
        channel->instrument->parameters[i].variable = channel->instrument->parameters[i].value;
    }

    for (int i = 0; i < ENVELOPE_NUMBER; i++)
    {
        int indice = channel->instrument->follow_indices[i];
        if (indice != -1)
        {
            float envelope = envelope_cycle(&channel->envelopes[i]) * channel->instrument->follow_values[i];
            channel->instrument->parameters[indice].variable = channel->instrument->parameters[indice].value + envelope;
        } 
    }

    switch (channel->instrument->type)
    {
    case INSTRUMENT_SUBSTRACTIVE:
        out = channel_substractive_cycle(channel);
        break;
    case INSTRUMENT_SAMPLER:
        out = channel_sampler_cycle(channel);
        break;
    }

    return out * channel->volume;
}

float channel_substractive_cycle(Channel *channel)
{

    float volume = channel->instrument->parameters[0].variable;
    float cutoff = channel->instrument->parameters[1].variable;
    float finetune = channel->instrument->parameters[2].variable;

    channel->osc.waveform_type = (int)channel->instrument->parameters[3].variable;

    channel->osc.frequency = channel->frequency + (finetune * 1000.0f);
    channel->filter.cutoff = cutoff * 10000.0f;

    float osc = osc_cycle(&channel->osc);
    float filter = filter_cycle(&channel->filter, osc);

    return filter * volume;
}

float channel_sampler_cycle(Channel *channel) {
    
    float out;

    float volume = channel->instrument->parameters[0].variable;

    channel->sampler.sample_start = channel->instrument->parameters[1].variable * channel->sampler.samples_size;
    channel->sampler.sample_end = channel->instrument->parameters[2].variable * channel->sampler.samples_size;
    if (channel->gate == 1) {
        channel->sampler.sample_position = channel->sampler.sample_start;
    }

    out = sampler_cycle(&channel->sampler) * volume;
    return out;
}

void channel_set_volume(Channel *channel, float volume)
{
    channel->volume = volume;
}

void channel_set_frequency(Channel *channel, float frequency)
{
    channel->frequency = frequency;
}

void channel_gate_on(Channel *channel)
{
    channel->gate = 1;
    for (int i = 0; i < ENVELOPE_NUMBER; i++)
    {
        envelope_gate_on(&channel->envelopes[i]);
    }
}

void channel_gate_off(Channel *channel)
{
    channel->gate = 0;
    for (int i = 0; i < ENVELOPE_NUMBER; i++)
    {
        envelope_gate_reset(&channel->envelopes[i]);
    }
}

void channel_set_instrument(Channel *channel, Instrument *instrument)
{
    channel->instrument = instrument;
}