#include "song_view.h"

#include "../graphics/graphics.h"
#include "../input/input.h"
#include "../common.h"
#include "../utils.h"

void song_view_init(SongView *song_view, Tracker *tracker, Graphics *graphics, Input *input)
{
    song_view->tracker = tracker;
    song_view->graphics = graphics;
    song_view->input = input;
}

void song_view_input(SongView *song_view)
{
    if (input_get(song_view->input, Shift))
    {
        if (input_get(song_view->input, Right))
        {
            song_view->tracker->song[song_view->cursor_x][song_view->cursor_y] = increase_index(song_view->tracker->song[song_view->cursor_x][song_view->cursor_y], CHAIN_SIZE);
        }

        if (input_get(song_view->input, Left))
        {
            song_view->tracker->song[song_view->cursor_x][song_view->cursor_y] = increase_index(song_view->tracker->song[song_view->cursor_x][song_view->cursor_y], CHAIN_SIZE);
        }
    }
    else if (input_get(song_view->input, Option))
    {
        if (input_get(song_view->input, Right))
        {
            song_view->tracker->mode = CHAIN_MODE;
            song_view->tracker->selected_chain = song_view->tracker->song[song_view->cursor_x][song_view->cursor_y];
        }
    }
    else if (input_get(song_view->input, Play))
    {

        song_view->tracker->playing = !song_view->tracker->playing;
    }
    else if (!input_get(song_view->input, Shift) && !input_get(song_view->input, Option) && !input_get(song_view->input, Play))
    {

        if (input_get(song_view->input, Left))
        {
            song_view->cursor_x = decrease_index(song_view->cursor_x, TRACK_SIZE);
        }

        if (input_get(song_view->input, Right))
        {
            song_view->cursor_x = increase_index(song_view->cursor_x, TRACK_SIZE);
        }

        if (input_get(song_view->input, Up))
        {
            song_view->cursor_y = decrease_index(song_view->cursor_y, SONG_SIZE);
        }

        if (input_get(song_view->input, Down))
        {
            song_view->cursor_y = increase_index(song_view->cursor_y, SONG_SIZE);
        }
    }
}

void song_view_render(SongView *song_view)
{

    int title_x = 0;
    int title_y = 0;

    int tracks_x = 0;
    int tracks_y = 16;

    int chains_x = 0;
    int chains_y = 32;

    graphics_render_text(song_view->graphics, 0, 0, "SONG");

    for (int i = 0; i < TRACK_SIZE; i++)
    {
        char c[2];
        sprintf(c, "%d", i + 1);
        graphics_render_text(song_view->graphics, tracks_x + i * (song_view->graphics->font_width + 2) * 2, tracks_y, c);

        for (int j = 0; j < SONG_SIZE; j++)
        {
            graphics_render_2_digit_int(song_view->graphics, chains_x + i * (song_view->graphics->font_width + 2) * 2, chains_y + j * song_view->graphics->font_height, song_view->tracker->song[i][j]);
        }
    }

    graphics_render_rect(song_view->graphics, chains_x + song_view->cursor_x * (song_view->graphics->font_width + 2) * 2, chains_y + song_view->cursor_y * song_view->graphics->font_height, song_view->graphics->font_width * 2, song_view->graphics->font_height);
}