#include "adsr.h"
#include <math.h>

void adsr_init(Adsr *adsr)
{
    adsr_reset(adsr);
    adsr_set_target_ratio_a(adsr, 0.3f);
    adsr_set_target_ratio_dr(adsr, 0.0001f);
    adsr_set_attack_rate(adsr, 0.01f * 44100.0f) ;
    adsr_set_decay_rate(adsr, 0.3f * 44100.0f);
    adsr_set_release_rate(adsr, 0.3f * 44100.0f);
    adsr_set_sustain_level(adsr, 0.0f);
}

void adsr_set_attack_rate(Adsr *adsr, float rate)
{
    adsr->attack_rate = rate;
    adsr->attack_coef = adsr_calc_coef(rate, adsr->target_ratio_a);
    adsr->attack_base = (1.0 + adsr->target_ratio_a) * (1.0 - adsr->attack_coef);
}

void adsr_set_decay_rate(Adsr *adsr, float rate)
{

    adsr->decay_rate = rate;
    adsr->decay_coef = adsr_calc_coef(rate, adsr->target_ratio_dr);
    adsr->decay_base = (adsr->sustain_level - adsr->target_ratio_dr) * (1.0 - adsr->decay_coef);
}

void adsr_set_release_rate(Adsr *adsr, float rate)
{

    adsr->release_rate = rate;
    adsr->release_coef = adsr_calc_coef(rate, adsr->target_ratio_dr);
    adsr->release_base = -adsr->target_ratio_dr * (1.0 - adsr->release_coef);
}

float adsr_calc_coef(float rate, float target_ratio)
{
    return exp(-log((1.0 + target_ratio) / target_ratio) / rate);
}

void adsr_set_sustain_level(Adsr *adsr, float level)
{
    adsr->sustain_level = level;
    adsr->decay_base = (adsr->sustain_level - adsr->target_ratio_dr) * (1.0 - adsr->decay_coef);
}

void adsr_set_target_ratio_a(Adsr *adsr, float target_ratio)
{
    if (target_ratio < 0.000000001)
        target_ratio = 0.000000001; // -180 dB
    adsr->target_ratio_a = target_ratio;
    adsr->attack_base = (1.0 + adsr->target_ratio_a) * (1.0 - adsr->attack_coef);
}

void adsr_set_target_ratio_dr(Adsr *adsr, float target_ratio)
{
    if (target_ratio < 0.000000001)
        target_ratio = 0.000000001; // -180 dB
    adsr->target_ratio_dr = target_ratio;
    adsr->decay_base = (adsr->sustain_level - adsr->target_ratio_dr) * (1.0 - adsr->decay_coef);
    adsr->release_base = -adsr->target_ratio_dr * (1.0 - adsr->release_coef);
}

float adsr_cycle(Adsr *adsr)
{
    switch (adsr->state)
    {
    case env_idle:
        break;
    case env_attack:
        adsr->output = adsr->attack_base + adsr->output * adsr->attack_coef;
        if (adsr->output >= 1.0)
        {
            adsr->output = 1.0;
            adsr->state = env_decay;
        }
        break;
    case env_decay:
        adsr->output = adsr->decay_base + adsr->output * adsr->decay_coef;
        if (adsr->output <= adsr->sustain_level)
        {
            adsr->output = adsr->sustain_level;
            adsr->state = env_sustain;
        }
        break;
    case env_sustain:
        break;
    case env_release:
        adsr->output = adsr->release_base + adsr->output * adsr->release_coef;
        if (adsr->output <= 0.0)
        {
            adsr->output = 0.0;
            adsr->state = env_idle;
        }
    }

    return adsr->output;
}

void adsr_gate(Adsr *adsr)
{
    if (adsr->gate == 0)
    {
        adsr->state = env_attack;
        adsr->gate = 1;
    }
    else if (adsr->state != env_idle)
    {
        adsr->state = env_release;
        adsr->gate = 0;
    }
}

int adsr_get_state(Adsr *adsr)
{
    return adsr->state;
}

void adsr_reset(Adsr *adsr)
{
    adsr->gate = 0;
    adsr->state = env_idle;
    adsr->output = 0.0;
}

float adsr_get_output(Adsr *adsr)
{
    return adsr->output;
}