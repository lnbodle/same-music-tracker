#include <stdio.h>
#include <stdlib.h>
#include "phrase_view.h"
#include "../common.h"
#include "../utils.h"
#include "../application/application.h"

void phrase_view_input(Application *app)
{

    if (input_get(&app->input, Edit))
    {

        if (input_get(&app->input, Option))
        {
            app->phrases[app->selected_phrase][app->cursor_y].note = -1;
            return;
        }

        if (app->phrases[app->selected_phrase][app->cursor_y].note == -1) {
            app->phrases[app->selected_phrase][app->cursor_y].note = 3;
            app->phrases[app->selected_phrase][app->cursor_y].octave = 5;
        }

        if (input_get(&app->input, Up))
        {
            app->phrases[app->selected_phrase][app->cursor_y].octave++;
        }

        if (input_get(&app->input, Down))
        {
            app->phrases[app->selected_phrase][app->cursor_y].octave--;
        }

        app->phrases[app->selected_phrase][app->cursor_y].octave = clamp_int(app->phrases[app->selected_phrase][app->cursor_y].octave, 0, 10);

        if (input_get(&app->input, Right))
        {
            switch (app->cursor_x)
            {

            case 0:
                app->phrases[app->selected_phrase][app->cursor_y].note++;
                break;

            case 1:
                app->phrases[app->selected_phrase][app->cursor_y].instrument++;
                break;
            }
        }

        if (input_get(&app->input, Left))
        {
            switch (app->cursor_x)
            {

            case 0:
                app->phrases[app->selected_phrase][app->cursor_y].note--;
                break;

            case 1:
                app->phrases[app->selected_phrase][app->cursor_y].instrument--;
                break;
            }
        }

        app->phrases[app->selected_phrase][app->cursor_y].note = clamp_int(app->phrases[app->selected_phrase][app->cursor_y].note, 0, 11);
        app->phrases[app->selected_phrase][app->cursor_y].instrument = clamp_int(app->phrases[app->selected_phrase][app->cursor_y].instrument, 0, INSTRUMENT_NUMBER);
        return;
    }

    if (input_get(&app->input, Shift))
    {
        if (input_get(&app->input, Right))
        {
            app->current_view_indice = VIEW_INSTRUMENT;
            app->selected_instrument = app->phrases[app->selected_phrase][app->cursor_y].instrument;
            application_reset_cursor(app);
        }
        if (input_get(&app->input, Left))
        {
            app->current_view_indice = VIEW_SONG;
            application_reset_cursor(app);
        }
        if (input_get(&app->input, Up))
        {
            app->selected_phrase --;
            application_reset_cursor(app);
        }
        if (input_get(&app->input, Down))
        {
            app->selected_phrase ++;
            application_reset_cursor(app);
        }
        app->selected_phrase = clamp_int(app->selected_phrase, 0, PHRASE_SIZE);
        return;
    }

    
    if (input_get(&app->input, Up))
    {
        app->cursor_y--;
    }

    if (input_get(&app->input, Down))
    {
        app->cursor_y++;
    }

    app->cursor_y = clamp_int(app->cursor_y, 0, STEP_PER_PHRASE - 1);

    if (input_get(&app->input, Right))
    {
        app->cursor_x++;
    }

    if (input_get(&app->input, Left))
    {
        app->cursor_x--;
    }

    app->cursor_x = clamp_int(app->cursor_x, 0, 1);
}

char NOTES[13] = {'A', 'A', 'B', 'C', 'C', 'D', 'D', 'E', 'F', 'F', 'G', 'G'};
int SHARPS[13] = {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1};

void phrase_view_render(Application *app)
{
    int title_x = 0;
    int title_y = 0;

    int steps_x = 0;
    int steps_y = app->font_height + 2;

    char phrase_info[16];
    sprintf(phrase_info, "PHRASE %d", app->selected_phrase);
    graphics_render_text(&app->graphics, title_x, title_y, phrase_info);


    int row_width = app->font_width * 3 + app->padding;

    graphics_render_rect(
        &app->graphics,
        steps_x + app->cursor_x * row_width,
        steps_y + app->cursor_y * app->font_height,
        app->font_width * 3,
        app->font_height);

    graphics_render_rect(
        &app->graphics,
        steps_x,
        steps_y + app->playing_step * app->font_height,
        4,
        app->font_height);

    for (int i = 0; i < STEP_PER_PHRASE; i++)
    {
        Step step = app->phrases[app->selected_phrase][i];

        char note_buffer[4];

        if (step.note == -1)
        {
            snprintf(note_buffer, sizeof(note_buffer), "---");
        }
        else
        {
            if (SHARPS[step.note])
            {
                snprintf(note_buffer, sizeof(note_buffer), "%c#%i", NOTES[step.note], step.octave);
            }
            else
            {
                snprintf(note_buffer, sizeof(note_buffer), "%c-%i", NOTES[step.note], step.octave);
            }
        }

        graphics_render_text(
            &app->graphics,
            steps_x,
            steps_y + i * app->font_height,
            note_buffer);

        graphics_render_2_digit_int(
            &app->graphics,
            steps_x + row_width,
            steps_y + i * app->font_height,
            step.instrument);
    }
}