#include "stdlib.h"
#include "tracker.h"
#include "../utils.h"

void tracker_init(Tracker *tracker, Sound *sound)
{
    tracker->sound = sound;
    tracker->playing_step = 0;
}

void tracker_cycle(Tracker *tracker)
{

    tracker->tick++;

    if (tracker->playing)
    {
        if (tracker->tick % 10 == 0)
        {
            for (int i = 0; i < CHANNEL_NUMBER; i++)
            {
                Channel *channel = sound_get_channel_by_id(tracker->sound, i);

                int phrase_index = tracker->chains[tracker->song[i][0]][0];

                Step step = tracker->phrases[phrase_index][tracker->playing_step];

                if (step.note != 0)
                {
                    float frequency = note_to_frequency(64 + step.note);
                    
                    channel_set_volume(channel,0.2f);
                    channel_set_frequency(channel, frequency);
                    channel_gate_off(channel);
                    channel_gate_on(channel);
                }
            }

            tracker->playing_step += 1;
            if (tracker->playing_step >= STEP_PER_PHRASE)
                tracker->playing_step = 0;
        }
    }
}