#include "chain_view.h"
#include "../common.h"
#include "../graphics/graphics.h"
#include "../input/input.h"
#include "../utils.h"

void chain_view_init(ChainView *chain_view, Tracker *tracker, Graphics *graphics, Input *input)
{
    chain_view->tracker = tracker;
    chain_view->graphics = graphics;
    chain_view->input = input;
}

void chain_view_input(ChainView *chain_view)
{
    if (input_get(chain_view->input, Edit))
    {
        return;
    }

    if (input_get(chain_view->input, Shift))
    {
        if (input_get(chain_view->input, Right))
        {
            chain_view->tracker->mode = PHRASE_MODE;
            chain_view->tracker->selected_phrase = chain_view->tracker->chains[chain_view->tracker->selected_chain][chain_view->cursor];
        }

        return;
    }

    if (input_get(chain_view->input, Play))
    {
        return;
    }

    if (input_get(chain_view->input, Up))
    {
        chain_view->cursor = decrease_index(chain_view->cursor, PHRASE_PER_CHAIN);
    }

    if (input_get(chain_view->input, Down))
    {
        chain_view->cursor = increase_index(chain_view->cursor, PHRASE_PER_CHAIN);
    }

    if (input_get(chain_view->input, Right))
    {
        chain_view->tracker->chains[chain_view->tracker->selected_chain][chain_view->cursor] = increase_index(chain_view->tracker->chains[chain_view->tracker->selected_chain][chain_view->cursor], CHAIN_SIZE);
    }

    if (input_get(chain_view->input, Left))
    {
        chain_view->tracker->chains[chain_view->tracker->selected_chain][chain_view->cursor] = decrease_index(chain_view->tracker->chains[chain_view->tracker->selected_chain][chain_view->cursor], CHAIN_SIZE);
    }
}

void chain_view_render(ChainView *chain_view)
{
    int title_x = 0;
    int title_y = 0;

    int phrases_x = 0;
    int phrases_y = 16;

    char chain_info[16];
    sprintf(chain_info, "CHAIN %d", chain_view->tracker->selected_chain);
    graphics_render_text(chain_view->graphics, title_x, title_y, chain_info);

    for (int i = 0; i < PHRASE_PER_CHAIN; i++)
    {
        graphics_render_2_digit_int(chain_view->graphics, phrases_x, phrases_y + i * chain_view->graphics->font_height, chain_view->tracker->chains[chain_view->tracker->selected_chain][i]);
    }

    graphics_render_rect(chain_view->graphics, phrases_x, phrases_y + chain_view->cursor * chain_view->graphics->font_height, chain_view->graphics->font_width * 2, chain_view->graphics->font_height);
}