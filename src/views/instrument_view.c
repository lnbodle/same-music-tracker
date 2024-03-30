#include "instrument_view.h"
#include "../utils.h"

void instrument_view_input(Application *app)
{

    if (input_get(&app->input, Shift))
    {
        if (input_get(&app->input, Left))
        {
            app->current_view_indice = VIEW_PHRASE;
            application_reset_cursor(app);
        }

        if (input_get(&app->input, Right))
        {
            app->current_view_indice = VIEW_ENVELOPES;
            application_reset_cursor(app);
        }
    }

    int index_p = app->instruments[app->selected_instrument].type;

    Parameter *selected_input = &app->instruments[app->selected_instrument].parameters[app->cursor_y];

    float increment = 0.1f;

    if (input_get(&app->input, Up) && input_get(&app->input, Option))
    {

        if (app->instruments[app->selected_instrument].type == 1)
        {

            app->instruments[app->selected_instrument].type = 0;
            instrument_set_type(&app->instruments[app->selected_instrument]);
        }
        // app->instruments[app->selected_instrument].type = clamp_int(app->instruments[app->selected_instrument].type,0,1);
        return;
    }

    if (input_get(&app->input, Down) && input_get(&app->input, Option))
    {
        if (app->instruments[app->selected_instrument].type == 0)
        {

            app->instruments[app->selected_instrument].type = 1;
            instrument_set_type(&app->instruments[app->selected_instrument]);
        }
        // app->instruments[app->selected_instrument].type = clamp_int(app->instruments[app->selected_instrument].type,0,1);
        return;
    }

    if (input_get(&app->input, Right) && input_get(&app->input, Edit))
    {
        selected_input->value += selected_input->increment_small;
        selected_input->value = clamp_float(selected_input->value, selected_input->min, selected_input->max);
        return;
    }

    if (input_get(&app->input, Left) && input_get(&app->input, Edit))
    {
        selected_input->value -= selected_input->increment_small;
        selected_input->value = clamp_float(selected_input->value, selected_input->min, selected_input->max);
        return;
    }

    if (input_get(&app->input, Up) && input_get(&app->input, Edit))
    {
        selected_input->value += selected_input->increment_high;
        selected_input->value = clamp_float(selected_input->value, selected_input->min, selected_input->max);
        return;
    }

    if (input_get(&app->input, Down) && input_get(&app->input, Edit))
    {
        selected_input->value -= selected_input->increment_high;
        selected_input->value = clamp_float(selected_input->value, selected_input->min, selected_input->max);
        return;
    }

    int r = -1;

    if (input_get(&app->input, Right))
    {

        int r = get_nearest_parameter(app, selected_input, 0);

        if (r != -1)
            app->cursor_y = r;
        return;
    }
    if (input_get(&app->input, Up))
    {
        int r = get_nearest_parameter(app, selected_input, 1);

        if (r != -1)
            app->cursor_y = r;
        return;
    }
    if (input_get(&app->input, Left))
    {
        int r = get_nearest_parameter(app, selected_input, 2);

        if (r != -1)
            app->cursor_y = r;
        return;
    }
    if (input_get(&app->input, Down))
    {
        int r = get_nearest_parameter(app, selected_input, 3);

        if (r != -1)
            app->cursor_y = r;
        return;
    }
}

char INSTRUMENT_TYPES[2][64] = {"Substractive", "Sampler"};

void instrument_view_render(Application *app)
{
    // graphics_render_text(&app->graphics,128,128, INSTRUMENT_TYPES[])

    int index_p = app->instruments[app->selected_instrument].type;

    graphics_render_text(&app->graphics, 128, 128, INSTRUMENT_TYPES[index_p]);

    for (int i = 0; i < app->instruments[app->selected_instrument].parameters_count; i++)
    {
        application_render_parameter(app, i, (i == app->cursor_y));
    }
}