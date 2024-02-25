#ifndef TRACKER_VIEW_H_
#define TRACKER_VIEW_H_

#include "../tracker/tracker.h"
#include "../graphics/graphics.h"

#include "song_view.h"
#include "chain_view.h"
#include "phrase_view.h"

typedef struct {

    Tracker *tracker;
    Graphics *graphics;
    Input *input;

    SongView song_view;
    ChainView chain_view;
    PhraseView phrase_view;
} TrackerView;

void tracker_view_init(TrackerView *tracker_view, Tracker *tracker, Graphics *graphics, Input *input);
void tracker_view_input(TrackerView *tracker_view);
void tracker_view_render(TrackerView *tracker_view);

#endif