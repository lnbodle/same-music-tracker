#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "osc.h"
#include "../common.h"

void osc_init(Osc *osc)
{

    osc->waveform_type = SINE;
}

float osc_cycle(Osc *osc)
{

    float delta_time = 1.0f / SAMPLE_RATE;
    osc->tick += delta_time;

    float output = 0;

    switch (osc->waveform_type)
    {
    case SINE:
        output = sin(2.f * (float)M_PI * osc->frequency * osc->tick);
        break;

    case SAW:
        output = osc->tick * osc->frequency;
        if (output > 1)
        {
            osc->tick = 0.0f;
        }
        break;

    default:
        break;
    }

    return output;
}