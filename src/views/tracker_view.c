#include "tracker_view.h"

void tracker_view_init(TrackerView *tracker_view, Tracker *tracker, Graphics *graphics, Input *input)
{
    tracker_view->tracker  = tracker;
    tracker_view->graphics = graphics;
    tracker_view->input    = input;

    song_view_init(&tracker_view->song_view, tracker, graphics, input);
    chain_view_init(&tracker_view->chain_view, tracker, graphics, input);
    phrase_view_init(&tracker_view->phrase_view, tracker, graphics, input);
}

void tracker_view_input(TrackerView *tracker_view)
{
    switch (tracker_view->tracker->mode)
    {
    case SONG_MODE:
        song_view_input(&tracker_view->song_view);
        break;
    case CHAIN_MODE:
        chain_view_input(&tracker_view->chain_view);
        break;
    case PHRASE_MODE:
        phrase_view_input(&tracker_view->phrase_view);
        break;
    }
}

void tracker_view_render(TrackerView *tracker_view)
{

    switch (tracker_view->tracker->mode)
    {
    case SONG_MODE:
        song_view_render(&tracker_view->song_view);
        break;
    case CHAIN_MODE:
        chain_view_render(&tracker_view->chain_view);
        break;
    case PHRASE_MODE:
        phrase_view_render(&tracker_view->phrase_view);
        break;
    }
}