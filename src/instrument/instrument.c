#include "instrument.h"
#include <string.h>

void instrument_init(Instrument *instrument)
{

    instrument->type = INSTRUMENT_SUBSTRACTIVE;

    instrument_set_type(instrument);
}

void instrument_set_type(Instrument *instrument) {

    instrument_free(instrument);

    if (instrument->type == INSTRUMENT_SUBSTRACTIVE)
    {
        Parameter volume = {"Volume", 0, 24, 1, 1, 0.01, 0.1, 0, 1};
        instrument_add_parameter(instrument, volume);

        Parameter cutoff = {"Cutoff", 0, 48, 1, 1, 0.01, 0.1, 0, 1};
        instrument_add_parameter(instrument, cutoff);

        Parameter finetune = {"Fintune", 0, 72, 0, 0, 0.01, 0.1, 0, 1};
        instrument_add_parameter(instrument, finetune);

        Parameter waveform = {"Waveform", 0, 72 + 24, 0, 0, 1, 1, 0, 4};
        instrument_add_parameter(instrument, waveform);
        return;
    }

    if (instrument->type == INSTRUMENT_SAMPLER)
    {
        Parameter volume = {"Volume", 0, 24, 1, 1, 0.01, 0.1, 0, 1};
        instrument_add_parameter(instrument, volume);

        Parameter sample_start = {"Start", 0, 48, 0, 1, 0.01, 0.1, 0, 1};
        instrument_add_parameter(instrument, sample_start);

        Parameter sample_end = {"End", 0, 72, 1, 1, 0.01, 0.1, 0, 1};
        instrument_add_parameter(instrument, sample_end);

        return;
    }
}

void instrument_free(Instrument *instrument) {


    for (int i = 0 ; i < 16 ; i++) {
        Parameter empty = {};
        instrument->parameters[i] = empty;
        instrument->parameters->label = 0;
    }
    instrument->parameters_count = 0;
}

void instrument_add_parameter(Instrument *instrument, Parameter parameter)
{
     

    //strcpy(instrument->parameters[instrument->parameters_count].label, parameter.label);
    instrument->parameters[instrument->parameters_count] = parameter;
    instrument->parameters_count++;
   
}
