#ifndef SAMPLER_H_
#define SAMPLER_H_

#include "../../libs/tinywav/tinywav.h"

#define SAMPLE_SIZE_POOL 1024 * 128

typedef struct
{
   TinyWav tw;
   char *file;
   int sample_position;
   int sample_start;
   int sample_end;
   float samples[SAMPLE_SIZE_POOL];
   int samples_size;
} Sampler;

void sampler_init(Sampler *sampler);
void sampler_load_sample(Sampler *sampler, char *file);
float sampler_cycle(Sampler *sampler);
void sampler_destroy(Sampler *sampler);

#endif