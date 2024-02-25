#ifndef CHANNEL_H_
#define CHANNEL_H_

#define CHANNEL_VOICE_NUMBER 8

#include "instrument.h"
#include "filter.h"
#include "adsr.h"

typedef enum {

    MONO,
    MINOR,
    MAJOR,
    MINOR_SEVEN,
    MAJOR_SEVEN

} ChordType;

typedef struct
{
    float tick;
    Instrument instruments[CHANNEL_VOICE_NUMBER];
    Filter filter;
    Adsr adsr;
    ChordType chord_type;
} Channel;

void channel_init(Channel *channel);
float channel_cycle(Channel *channel);
void channel_set_frequency(Channel *channel, float frequency);
void channel_gate_on(Channel *channel);
void channel_gate_off(Channel *channel);

#endif