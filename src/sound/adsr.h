#ifndef ADSR_H_
#define ADSR_H_

enum adsrState
{
    env_idle = 0,
    env_attack,
    env_decay,
    env_sustain,
    env_release
};

typedef struct
{
    int state;
    float output;
    float attack_rate;
    float decay_rate;
    float release_rate;
    float attack_coef;
    float decay_coef;
    float release_coef;
    float sustain_level;
    float target_ratio_a;
    float target_ratio_dr;
    float attack_base;
    float decay_base;
    float release_base;
    int gate;

} Adsr;

void adsr_init(Adsr *adsr);
float adsr_calc_coef(float rate, float target_ratio);
float adsr_cycle(Adsr *adsr);
float adsr_get_output(Adsr *adsr);
int adsr_get_state(Adsr *adsr);
void adsr_gate(Adsr *adsr);
void adsr_set_attack_rate(Adsr *adsr, float rate);
void adsr_set_decay_rate(Adsr *adsr, float rate);
void adsr_set_release_rate(Adsr *adsr, float rate);
void adsr_set_sustain_level(Adsr *adsr, float level);
void adsr_set_target_ratio_a(Adsr *adsr, float target_ratio);
void adsr_set_target_ratio_dr(Adsr *adsr, float target_ratio);
void adsr_reset(Adsr *adsr);

#endif