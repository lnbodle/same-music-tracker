#include "stdlib.h"
#include "tracker_engine.h"
#include "../utils.h"

void tracker_engine_init(TrackerEngine *tracker_engine, SoundEngine *sound_engine)
{

    tracker_engine->sound_engine = sound_engine;

    tracker_engine->current_step_index = 0;

    for (int i = 0; i < CHANNEL_NUMBER; i++)
    {
        tracker_engine->song[0][i] = i;
        tracker_engine->chains[i]  = i;
    }

    for (int i = 0; i < STEP_NUMBER; i++)
    {
        tracker_engine->phrases[i].steps[i].note = 12 + rand() % 12;
    }
}

void tracker_engine_cycle(TrackerEngine *tracker_engine)
{

    tracker_engine->tick++;

    if (tracker_engine->tick % 15 == 0)
    {

        for (int i = 0; i < CHANNEL_NUMBER; i++)
        {

            Channel *channel = sound_engine_get_channel_by_id(tracker_engine->sound_engine, i);

            /*Step current_step = tracker_engine->chains[0].phrases[0].steps[tracker_engine->current_step_index];

            float frequency = note_to_frequency(current_step.note);
            channel_set_frequency(channel, frequency);
            channel_gate_off(channel);
            channel_gate_on(channel);*/
        }

        tracker_engine->current_step_index += 1;
        if (tracker_engine->current_step_index >= STEP_NUMBER)
            tracker_engine->current_step_index = 0;
    }
}