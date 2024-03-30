#include "adsr.h"
#include "envelope.h"

void envelope_init(Envelope *envelope)
{
    envelope->type = ENVELOPE_ADSR;
    envelope->gate = 0.0f;

    switch (envelope->type)
    {
    case ENVELOPE_ADSR:
        adsr_init(&envelope->adsr);
        break;

    case ENVELOPE_LFO:

        break;
    }
}

float envelope_cycle(Envelope *envelope)
{

    float out = 0.0f;

    switch (envelope->type)
    {
    case ENVELOPE_ADSR:
        out = adsr_cycle(&envelope->adsr);
        break;

    case ENVELOPE_LFO:

        break;
    }

    return out;
}

float envelope_gate_on(Envelope *envelope)
{

    adsr_gate(&envelope->adsr);
}

float envelope_gate_reset(Envelope *envelope)
{

    adsr_reset(&envelope->adsr);
}