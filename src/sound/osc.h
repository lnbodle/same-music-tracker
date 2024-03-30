#ifndef OSC_H_
#define OSC_H_

typedef enum {
    SINE,
    TRIANGLE,
    SAW,
    SQUARE,
    NOISE
} WaveformType;

typedef struct  {

    float tick;
    float frequency;
    float phase;
    int waveform_type;
} Osc;

void osc_init(Osc *osc);
float osc_cycle(Osc *osc);

#endif