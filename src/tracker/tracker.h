#ifndef TRACKER_H_
#define TRACKER_H_

#define STEP_NUMBER 16
#define PHRASE_NUMBER 16
#define CHAIN_NUMBER 16

#include "../sound/sound.h"

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

typedef int Song[CHANNEL_NUMBER][CHAIN_NUMBER];

typedef struct {

    int current_step_index;
    int current_phrase_index;
    int current_chain_index;
    int tick;

    int song_x;

    Song song;
    int chains[CHAIN_NUMBER];
    Phrase phrases[PHRASE_NUMBER];

    Sound *sound;
} Tracker;


void tracker_init(Tracker *tracker, Sound *sound);
void tracker_cycle(Tracker *tracker);

#endif