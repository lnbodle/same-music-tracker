#ifndef SOUND_H_
#define SOUND_H_

#include "channel.h"

#define CHANNEL_NUMBER 16

typedef struct {

    Channel channels[CHANNEL_NUMBER];
} Sound;

void sound_init(Sound *sound);
float sound_cycle(Sound *sound);
Channel* sound_get_channel_by_id(Sound *sound, int channel_id);

#endif