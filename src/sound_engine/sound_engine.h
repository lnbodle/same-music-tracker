#ifndef SOUND_ENGINE_H_
#define SOUND_ENGINE_H_

#include "channel.h"

#define CHANNEL_NUMBER 16

typedef struct {

    Channel channels[CHANNEL_NUMBER];
} SoundEngine;

void sound_engine_init(SoundEngine *sound_engine);
float sound_engine_cycle(SoundEngine *sound_engine);
Channel* sound_engine_get_channel_by_id(SoundEngine *sound_engine, int channel_id);

#endif