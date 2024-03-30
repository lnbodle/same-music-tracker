#include "sampler.h"
#include "../common.h"
#include <assert.h>

#define NUM_CHANNELS 2
#define BLOCK_SIZE 480

void sampler_init(Sampler *sampler)
{
}

void sampler_load_sample(Sampler *sampler, char *file)
{
    tinywav_open_read(&sampler->tw, "samples/lil peep pad (1).wav", TW_INTERLEAVED);

    int total_samples = sampler->tw.numFramesInHeader;
    int rate    = sampler->tw.h.SampleRate;

    int samplesProcessed = 0;

    int index = 0;
    while(samplesProcessed < total_samples) {

        float buffer[NUM_CHANNELS];

        int samplesRead = tinywav_read_f(&sampler->tw, buffer, 1);
        assert(samplesRead > 0 && " Could not read from file!");

        if (index < SAMPLE_SIZE_POOL) {
            sampler->samples[index] = buffer[0];
            sampler->samples_size ++;
        }

        samplesProcessed += samplesRead * NUM_CHANNELS;
        index++;
    }
    tinywav_close_read(&sampler->tw);
}

float sampler_cycle(Sampler *sampler)
{

    if (sampler->sample_position < sampler->sample_end) {
        sampler->sample_position++;
        return sampler->samples[sampler->sample_position];
    }

    return 0;
}

void sampler_destroy(Sampler *sampler)
{

    tinywav_close_read(&sampler->tw);
}