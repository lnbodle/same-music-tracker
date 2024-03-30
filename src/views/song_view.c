#include <stdio.h>

#include "song_view.h"

#include "../common.h"
#include "../utils.h"
#include "../application/application.h"

void song_view_input(Application *app)
{

    if (input_get(&app->input, Edit))
    {
        if (input_get(&app->input, Right))
        {
            app->song[app->cursor_x][app->cursor_y]++;
        }

        if (input_get(&app->input, Left))
        {
            app->song[app->cursor_x][app->cursor_y]--;
        }

        app->song[app->cursor_x][app->cursor_y] = clamp_int(app->song[app->cursor_x][app->cursor_y], -1, PHRASE_SIZE);
        return;
    }

    if (input_get(&app->input, Shift))
    {
        if (input_get(&app->input, Right) && app->song[app->cursor_x][app->cursor_y] != -1)
        {
            app->current_view_indice = VIEW_PHRASE;
            app->selected_phrase = app->song[app->cursor_x][app->cursor_y];
            application_reset_cursor(app);
        }
        return;
    }

    if (input_get(&app->input, Left))
    {
        app->cursor_x--;
    }

    if (input_get(&app->input, Right))
    {
        app->cursor_x++;
    }

    if (input_get(&app->input, Up))
    {
        app->cursor_y--;
    }

    if (input_get(&app->input, Down))
    {
        app->cursor_y++;
    }

    app->cursor_x = clamp_int(app->cursor_x, 0, TRACK_SIZE - 1);
    app->cursor_y = clamp_int(app->cursor_y, 0, SONG_SIZE - 1);
}

void song_view_render(Application *app)
{

    int title_x = 0;
    int title_y = 0;

    int tracks_x = 0;
    int tracks_y = app->font_height + 2;

    int chains_x = 0;
    int chains_y = (app->font_height * 2) + 2;

    graphics_render_text(
        &app->graphics,
        title_x,
        title_y,
        "SONG");

    int row_width = app->font_width * 2 + app->padding;

    graphics_render_rect(
        &app->graphics,
        chains_x + app->cursor_x * row_width,
        chains_y + app->cursor_y * app->font_height,
        app->font_width * 2,
        app->font_height);

    graphics_render_rect(
        &app->graphics,
        chains_x,
        chains_y + app->playing_phrase * app->font_height,
        480,
        app->font_height);

    for (int i = 0; i < TRACK_SIZE; i++)
    {

        char c[2];
        sprintf(c, "%d", i + 1);
        graphics_render_text(
            &app->graphics,
            tracks_x + i * row_width,
            tracks_y,
            c);

        for (int j = 0; j < SONG_SIZE; j++)
        {
            if (app->song[i][j] != -1)
            {
                graphics_render_2_digit_int(
                    &app->graphics,
                    chains_x + i * row_width,
                    chains_y + j * app->font_height,
                    app->song[i][j]);
            }
            else
            {
                graphics_render_text(
                    &app->graphics,
                    chains_x + i * row_width,
                    chains_y + j * app->font_height,
                    "--");
            }
        }
    }
}