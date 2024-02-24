#include "stdlib.h"
#include "tracker.h"
#include "../utils.h"

void tracker_init(Tracker *tracker, Sound *sound)
{

    tracker->sound = sound;

    tracker->current_step_index = 0;

    for (int i = 0; i < CHANNEL_NUMBER; i++)
    {
        tracker->song[i][0] = i;
        tracker->chains[i]  = i;

        for (int j = 0 ; j < STEP_NUMBER ; j++) {
            tracker->phrases[i].steps[j].note = 78 + rand() % 12;
        }
    }
}

void tracker_cycle(Tracker *tracker)
{

    tracker->tick++;

    if (tracker->tick % 15 == 0)
    {

        for (int i = 0; i < CHANNEL_NUMBER; i++)
        {

            Channel *channel = sound_get_channel_by_id(tracker->sound, i);

            //Step current_step = tracker->chains[0].phrases[0].steps[tracker->current_step_index];

            int chain = tracker->chains[tracker->song[i][0]];

            Phrase phrase = tracker->phrases[chain];

            Step step = phrase.steps[tracker->current_step_index];

            float frequency = note_to_frequency(step.note);
            channel_set_frequency(channel, frequency);
            channel_gate_off(channel);
            channel_gate_on(channel);
        }

        tracker->current_step_index += 1;
        if (tracker->current_step_index >= STEP_NUMBER)
            tracker->current_step_index = 0;
    }
}