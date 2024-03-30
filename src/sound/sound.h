#ifndef SOUND_H_
#define SOUND_H_

#include "channel.h"
#include "../common.h"

typedef struct {

    Channel channels[CHANNEL_NUMBER];

    //Instrument instruments[INSTRUMENT_NUMBER];

    /*sp_data *sp;*/
} Sound;

void sound_init(Sound *sound);
void sound_free(Sound *sound);
float sound_cycle(Sound *sound);
Channel* sound_get_channel_by_id(Sound *sound, int channel_id);

#endif