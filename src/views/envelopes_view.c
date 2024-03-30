#include "envelopes_view.h"
#include "../utils.h"

void envelopes_view_input(Application *app)
{

    if (input_get(&app->input, Edit))
    {
        if (input_get(&app->input, Option))
        {
            switch (app->cursor_y)
            {

            case 0:
                app->instruments[app->selected_instrument].follow_indices[app->cursor_x] = -1;
                break;
            }
            return;
        }

        if (input_get(&app->input, Right))
        {
            switch (app->cursor_y)
            {

            case 0:
                app->instruments[app->selected_instrument].follow_indices[app->cursor_x]++;
                break;

            case 1:
                app->instruments[app->selected_instrument].follow_values[app->cursor_x] += 0.1;
                break;
            }
        }

        if (input_get(&app->input, Left))
        {
            switch (app->cursor_y)
            {

            case 0:
                app->instruments[app->selected_instrument].follow_indices[app->cursor_x]--;
                break;

            case 1:
                app->instruments[app->selected_instrument].follow_values[app->cursor_x] -= 0.1;
                break;
            }
        }

        app->instruments[app->selected_instrument].follow_indices[app->cursor_x] = clamp_int(app->instruments[app->selected_instrument].follow_indices[app->cursor_x], 0, 4);
        app->instruments[app->selected_instrument].follow_values[app->cursor_x] = clamp_float(app->instruments[app->selected_instrument].follow_values[app->cursor_x], 0, 1.0f);
        return;
    }

    if (input_get(&app->input, Shift))
    {
        if (input_get(&app->input, Left))
        {
            app->current_view_indice = VIEW_INSTRUMENT;
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

    app->cursor_x = clamp_int(app->cursor_x, 0, 3);

    if (input_get(&app->input, Up))
    {
        app->cursor_y--;
    }

    if (input_get(&app->input, Down))
    {
        app->cursor_y++;
    }

    app->cursor_y = clamp_int(app->cursor_y, 0, 1);
}

void envelopes_view_render(Application *app)
{

    int title_x = 0;
    int title_y = 0;

    int envelopes_x = 0;
    int envelopes_y = app->font_height + 2;

    char chain_info[16];
    sprintf(chain_info, "ENVELOPES %d", app->selected_instrument);
    graphics_render_text(&app->graphics, title_x, title_y, chain_info);

    int row_width = app->font_width * 9 + app->padding;

    graphics_render_rect(
        &app->graphics,
        envelopes_x + app->cursor_x * row_width,
        envelopes_y + app->cursor_y * app->font_height,
        row_width,
        app->font_height);

    for (int i = 0; i < ENVELOPE_NUMBER; i++)
    {
        int indice = app->instruments[app->selected_instrument].follow_indices[i];

        if (indice != -1)
        {
            graphics_render_text(
                &app->graphics,
                envelopes_x + i * row_width,
                envelopes_y,
                app->instruments[app->selected_instrument].parameters[indice].label);
        }
        else
        {
            graphics_render_text(
                &app->graphics,
                envelopes_x + i * row_width,
                envelopes_y,
                "--");
        }

        graphics_render_float(
            &app->graphics,
            envelopes_x + i * row_width,
            envelopes_y + app->font_height,
            app->instruments[app->selected_instrument].follow_values[i]);
    }
}