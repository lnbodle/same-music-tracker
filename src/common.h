#ifndef COMMON_H_
#define COMMON_H_

#define SAMPLE_RATE 44100
#define SAMPLES 1024

#define STEP_PER_PHRASE 16

#define TRACK_SIZE 8
#define SONG_SIZE 16

#define PHRASE_SIZE 99
#define PHRASE_PER_CHAIN 1

#define CHAIN_SIZE 4
#define CHAIN_PER_SONG 1

#define CHANNEL_NUMBER 8

#define INSTRUMENT_NUMBER 16

#define ENVELOPE_NUMBER 4
#define FLOAT_PARAMETER_NUMBER 4
#define INT_PARAMETER_NUMBER 4

typedef enum {
    INSTRUMENT_SUBSTRACTIVE,
    INSTRUMENT_SAMPLER
} InstrumentTypes;

typedef struct {
    char *label;
    int x;
    int y;
    float value;
    float default_value;
    float increment_small;
    float increment_high;
    float min;
    float max;
    float variable;
} Parameter;

#endif