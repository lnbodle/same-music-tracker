#ifndef SONG_VIEW_H_
#define SONG_VIEW_H_

#include "../tracker/tracker.h"
#include "../graphics/graphics.h"
#include "../input/input.h"

typedef struct {

    int cursor_x;
    int cursor_y;

    Tracker *tracker;
    Graphics *graphics;
    Input *input;

} SongView;

void song_view_init(SongView *song_view, Tracker *tracker, Graphics *graphics, Input *input);
void song_view_input(SongView *song_view);
void song_view_render(SongView *song_view);

#endif