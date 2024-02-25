#ifndef PHRASE_VIEW_H_
#define PHRASE_VIEW_H_

#include "../tracker/tracker.h"
#include "../graphics/graphics.h"
#include "../input/input.h"

typedef struct {

    int cursor;

    Tracker *tracker;
    Graphics *graphics;
    Input *input;

} PhraseView;

void phrase_view_init(PhraseView *phrase_view, Tracker *tracker, Graphics *graphics, Input *input);
void phrase_view_input(PhraseView *phrase_view);
void phrase_view_render(PhraseView *phrase_view);

#endif