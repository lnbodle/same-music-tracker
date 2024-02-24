#ifndef TRACKER_H_
#define TRACKER_H_

#define STEP_NUMBER 16
#define PHRASE_NUMBER 16
#define CHAIN_NUMBER 16

#include "../sound_engine/sound_engine.h"

typedef struct {

    int note;
    int instrument;
} Step;

typedef struct {

    Step steps[STEP_NUMBER];
} Phrase;

typedef enum {

    SONG_MODE,
    CHAIN_MODE,
    PHRASE_MODE,

} TrackerMode;

typedef struct {

    int current_step_index;
    int current_phrase_index;
    int current_chain_index;
    int tick;

    int song[CHANNEL_NUMBER][CHAIN_NUMBER];
    int chains[CHAIN_NUMBER];
    Phrase phrases[PHRASE_NUMBER];

    SoundEngine *sound_engine;
} TrackerEngine;


void tracker_engine_init(TrackerEngine *tracker, SoundEngine *sound_engine);
void tracker_engine_cycle(TrackerEngine *tracker);

#endif