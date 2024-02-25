#include "instrument.h"

void instrument_init(Instrument *instrument)
{
    instrument->type = SIMPLE;

    switch (instrument->type)
    {

    case SIMPLE:
        osc_init(&instrument->osc);
        break;
    }
}
float instrument_cycle(Instrument *instrument)
{

    switch (instrument->type)
    {
    case SIMPLE:
        instrument->osc.frequency = instrument->frequency;
        return osc_cycle(&instrument->osc);
        break;
    }
}