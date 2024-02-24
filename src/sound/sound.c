#include <math.h>
#include <stdlib.h>

#include "channel.h"
#include "sound.h"

void sound_init(Sound *sound) {

    int out = 0;
    
    for (int i = 0 ; i < CHANNEL_NUMBER; i++) {

        channel_init(&sound->channels[i]);
    }
}

float sound_cycle(Sound *sound) {

    float out = 0;

    for (int i = 0 ; i < CHANNEL_NUMBER; i++) {

        out += channel_cycle(&sound->channels[i]) / CHANNEL_NUMBER;
    }

    return out;
}

Channel* sound_get_channel_by_id(Sound *sound, int channel_id) {

    return &sound->channels[channel_id];
}