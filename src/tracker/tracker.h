#ifndef TRACKER_H_
#define TRACKER_H_

#include "../sound/sound.h"
#include "../common.h"

typedef struct {

    int note;
    int octave;
    int volume;
    int instrument;
} Step;

typedef enum {

    SONG_MODE,
    CHAIN_MODE,
    PHRASE_MODE,
} TrackerMode;

typedef struct {

    int tick;

    int playing_step;
    int playing_phrase;
    int playing_chains;

    int selected_phrase;
    int selected_chain;
    int selected_step;

    int selected_song_x;
    int selected_song_y;

    int playing;

    int song[CHANNEL_NUMBER][CHAIN_PER_SONG]; 
    int chains[CHAIN_SIZE][PHRASE_PER_CHAIN];
    Step phrases[PHRASE_SIZE][STEP_PER_PHRASE];

    TrackerMode mode;
    Sound *sound;

} Tracker;

void tracker_init(Tracker *tracker, Sound *sound);
void tracker_cycle(Tracker *tracker);

#endif