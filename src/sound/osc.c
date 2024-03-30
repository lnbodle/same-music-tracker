#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "osc.h"
#include "../common.h"

void osc_init(Osc *osc)
{
    osc->waveform_type = SQUARE;
}

float osc_cycle(Osc *osc)
{
    float delta_time = 1.0f / (float)SAMPLE_RATE;

    float delta = delta_time * osc->frequency * 360.0f;

    osc->phase += delta;

    if (osc->phase >= 360.0f)
        osc->phase = 0.0f;

    float output = 0;

    switch (osc->waveform_type)
    {
    case SINE:
        output = (float)sin(osc->phase * M_PI / 180.0f);
        break;
    case TRIANGLE:              
        output = (float)(abs(osc->phase / 180.0f - 1.0f) - 0.5f) * 2.0f;
        break;
    case SAW:
        output = osc->phase / 180.0f - 1.0f;
        break;
    case SQUARE:
        if (osc->phase >= 180.0f)
        {
            return 1.0f;
        }
        else
        {
            return 0.0f;
        }
        break;
    case NOISE:
        output = (float)(rand() % 1000) / 1000.0f;
        break;
    default:
        break;
    }

    return output;
}