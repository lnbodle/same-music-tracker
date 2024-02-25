#include "osc.h"

typedef enum {
    SIMPLE,
} InstrumentType;

typedef struct {

    char name[16];
    float value;
} Parameter;

typedef struct {

    int type;
    Osc osc;

    float frequency;

    Parameter parameters[16];
} Instrument;


void instrument_init(Instrument *instrument);
float instrument_cycle(Instrument *instrument);