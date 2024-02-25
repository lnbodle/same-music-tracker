#ifndef CHAIN_VIEW_H_
#define CHAIN_VIEW_H_

#include "../tracker/tracker.h"
#include "../graphics/graphics.h"
#include "../input/input.h"

typedef struct {

    int cursor;

    Tracker *tracker;
    Graphics *graphics;
    Input *input;

} ChainView;

void chain_view_init(ChainView *chain_view, Tracker *tracker, Graphics *graphics, Input *input);
void chain_view_input(ChainView *chain_view);
void chain_view_render(ChainView *chain_view);

#endif