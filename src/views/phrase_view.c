#include <stdio.h>
#include <stdlib.h>

#include "phrase_view.h"
#include "../common.h"
#include "../graphics/graphics.h"
#include "../input/input.h"
#include "../utils.h"

void phrase_view_init(PhraseView *phrase_view, Tracker *tracker, Graphics *graphics, Input *input)
{

    phrase_view->tracker = tracker;
    phrase_view->graphics = graphics;
    phrase_view->input = input;
}

void phrase_view_input(PhraseView *phrase_view)
{
    if (input_get(phrase_view->input, Shift))
    {

        if (input_get(phrase_view->input, Right))
        {
            phrase_view->tracker->phrases[phrase_view->tracker->selected_phrase][phrase_view->tracker->selected_step].octave = increase_index(phrase_view->tracker->phrases[phrase_view->tracker->selected_phrase][phrase_view->tracker->selected_step].octave, 10);
        }

        if (input_get(phrase_view->input, Left))
        {
            phrase_view->tracker->phrases[phrase_view->tracker->selected_phrase][phrase_view->tracker->selected_step].octave = decrease_index(phrase_view->tracker->phrases[phrase_view->tracker->selected_phrase][phrase_view->tracker->selected_step].octave, 10);
        }
    }
    else if (input_get(phrase_view->input, Option))
    {
        if (input_get(phrase_view->input, Right))
        {
            phrase_view->tracker->mode = SONG_MODE;
        }
    }
    else if (input_get(phrase_view->input, Play))
    {
    }
    else if (!input_get(phrase_view->input, Shift) && !input_get(phrase_view->input, Option) && !input_get(phrase_view->input, Play))
    {
        if (input_get(phrase_view->input, Up))
        {
            phrase_view->tracker->selected_step = decrease_index(phrase_view->tracker->selected_step, STEP_PER_PHRASE);
        }

        if (input_get(phrase_view->input, Down))
        {
            phrase_view->tracker->selected_step = increase_index(phrase_view->tracker->selected_step, STEP_PER_PHRASE);
        }

        if (input_get(phrase_view->input, Right))
        {
            phrase_view->tracker->phrases[phrase_view->tracker->selected_phrase][phrase_view->tracker->selected_step].note = increase_index(phrase_view->tracker->phrases[phrase_view->tracker->selected_phrase][phrase_view->tracker->selected_step].note, 8);
        }

        if (input_get(phrase_view->input, Left))
        {
            phrase_view->tracker->phrases[phrase_view->tracker->selected_phrase][phrase_view->tracker->selected_step].note = decrease_index(phrase_view->tracker->phrases[phrase_view->tracker->selected_phrase][phrase_view->tracker->selected_step].note, 8);
        }
    }
}

char NOTES[8] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G'};

void phrase_view_render(PhraseView *phrase_view)
{
    int title_x = 0;
    int title_y = 0;

    int steps_x = 0;
    int steps_y = 16;

    char phrase_info[16];
    sprintf(phrase_info, "PHRASE %d", phrase_view->tracker->selected_phrase);
    graphics_render_text(phrase_view->graphics, title_x, title_y, phrase_info);

    for (int i = 0; i < STEP_PER_PHRASE; i++)
    {
        Step step = phrase_view->tracker->phrases[phrase_view->tracker->selected_phrase][i];

        char note_buffer[4];

        if (step.note == 0)
        {

            snprintf(note_buffer, sizeof(note_buffer), "---");
        }
        else
        {

            snprintf(note_buffer, sizeof(note_buffer), "%c-%i", NOTES[step.note], step.octave);
        }

        graphics_render_text(phrase_view->graphics, steps_x, steps_y + i * phrase_view->graphics->font_height, note_buffer);

        graphics_render_2_digit_int(phrase_view->graphics, steps_x + phrase_view->graphics->font_width * 4, steps_y + i * phrase_view->graphics->font_height, step.volume);
    }

    graphics_render_rect(phrase_view->graphics, steps_x, steps_y + phrase_view->tracker->playing_step * phrase_view->graphics->font_height, phrase_view->graphics->font_width / 4, phrase_view->graphics->font_height);
    graphics_render_rect(phrase_view->graphics, steps_x, steps_y + phrase_view->tracker->selected_step * phrase_view->graphics->font_height, phrase_view->graphics->font_width * 3, phrase_view->graphics->font_height);
}