#include <math.h>
#include <stdlib.h>

#include "channel.h"
#include "sound_engine.h"

void sound_engine_init(SoundEngine *sound_engine) {

    int out = 0;
    
    for (int i = 0 ; i < CHANNEL_NUMBER; i++) {

        channel_init(&sound_engine->channels[i]);
    }
}

float sound_engine_cycle(SoundEngine *sound_engine) {

    float out = 0;

    for (int i = 0 ; i < CHANNEL_NUMBER; i++) {

        out += channel_cycle(&sound_engine->channels[i]) / CHANNEL_NUMBER;
    }

    return out;
}

Channel* sound_engine_get_channel_by_id(SoundEngine *sound_engine, int channel_id) {

    return &sound_engine->channels[channel_id];
}