#include <string.h>
#include <math.h>

#include "../sound/sound.h"
#include "../utils.h"

#include "../views/song_view.h"
#include "../views/phrase_view.h"
#include "../views/instrument_view.h"
#include "../views/envelopes_view.h"

void application_init(
    Application *app,
    void *render_rect_callback,
    void *render_text_callback)
{
    app->current_view_indice = 0;

    app->playing_step = 0;
    app->tempo = 40;

    app->padding = 16;
    app->font_width = 13;
    app->font_height = 24;

    for (int i = 0; i < 4; i++)
    {
        instrument_init(&app->instruments[i]);
    }

    sound_init(&app->sound);

    for (int i = 0; i < PHRASE_SIZE; i++)
    {
        for (int j = 0; j < STEP_PER_PHRASE; j++)
        {
            app->phrases[i][j].note = -1;
        }
    }

    for (int i = 0; i < TRACK_SIZE; i++)
    {
        for (int j = 0; j < SONG_SIZE; j++)
        {
            app->song[i][j] = -1;
        }
    }
}

void application_input(Application *application)
{
    if (input_get(&application->input, Play))
    {
        application->playing_step = 0;
        application->playing_phrase = 0;
        application->playing = !application->playing;
    }

    switch (application->current_view_indice)
    {
    case VIEW_SONG:
        song_view_input(application);
        break;
    case VIEW_PHRASE:
        phrase_view_input(application);
        break;
    case VIEW_INSTRUMENT:
        instrument_view_input(application);
        break;
    case VIEW_ENVELOPES:
        envelopes_view_input(application);
        break;
    }
}

void application_render(Application *application)
{

    switch (application->current_view_indice)
    {
    case VIEW_SONG:
        song_view_render(application);
        break;
    case VIEW_PHRASE:
        phrase_view_render(application);
        break;
    case VIEW_INSTRUMENT:
        instrument_view_render(application);
        break;
    case VIEW_ENVELOPES:
        envelopes_view_render(application);
        break;
    }
}

int get_nearest_parameter(Application *app, Parameter *input, int check)
{

    double final_distance = 9999999;
    int r = -1;

    for (int i = 0; i < app->instruments[app->selected_instrument].parameters_count; i++)
    {

        Parameter *other = &app->instruments[app->selected_instrument].parameters[i];

        if (other == input)
            continue;

        float dir = (atan2(other->y - input->y, input->x - other->x) * (180 / M_PI)) + 180;

        float current = (float)check * 90;

        float anglediff = (int)(dir - current + 180 + 360) % 360 - 180;

        double dist = 0;

        // Horizontal
        if (check == 0 && check == 2)
        {
            dist = distance(input->x, 0, other->x, 0);
        }
        else
        {
            dist = distance(0, input->y, 0, other->y);
        }

        if (anglediff <= 89.9 && anglediff >= -89.9)
        {
        }
        else
        {
            continue;
        }

        if (dist < final_distance)
        {
            final_distance = dist;
            r = i;
        }
    }

    return r;
}

void application_cycle(Application *app)
{

    float beat_time = (float)1.0f / (float)SAMPLE_RATE;
    app->tick += beat_time;

    float n = (beat_time * 6.0f * 60.0f) / app->tempo;

    if (app->playing)
    {
        if (app->tick >= n)
        {
            for (int i = 0; i < CHANNEL_NUMBER; i++)
            {
                Channel *channel = sound_get_channel_by_id(&app->sound, i);

                channel_gate_off(channel);

                int phrase_index = app->song[i][app->playing_phrase];

                if (phrase_index != -1)
                {
                    Step step = app->phrases[phrase_index][app->playing_step];

                    if (step.note != -1)
                    {
                        float frequency = note_to_frequency((step.octave * 12) + step.note);

                        channel_set_instrument(channel, &app->instruments[step.instrument]);
                        channel_set_volume(channel, 0.5f);
                        channel_set_frequency(channel, frequency);

                        channel_gate_on(channel);
                    }
                }
            }

            app->playing_step += 1;
            if (app->playing_step >= STEP_PER_PHRASE)
            {
                app->playing_step = 0;
                //app->playing_phrase += 1;
            }

            /*if (app->playing_phrase >= SONG_SIZE)
            {
                app->playing_phrase = 0;
            }*/

            app->tick = 0.0f;
        }
    }
}

void application_render_parameter(Application *app, int index, int selected)
{

    // int index_p = app->instruments[app->selected_instrument].type;
    Parameter input = app->instruments[app->selected_instrument].parameters[index];

    int text_width = app->font_width * 16 + 1;

    if (selected)
    {
        graphics_render_rect(&app->graphics, input.x, input.y, text_width, app->font_height);
    }

    graphics_render_text(
        &app->graphics,
        input.x,
        input.y,
        input.label);

    graphics_render_float(
        &app->graphics,
        input.x + text_width,
        input.y,
        input.value);
}

void application_reset_cursor(Application *application)
{
    application->cursor_x = 0;
    application->cursor_y = 0;
}

void application_free(Application *app)
{
    sound_free(&app->sound);
}