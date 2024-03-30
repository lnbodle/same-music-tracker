#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"

void graphics_render_rect(Graphics *graphics, int x, int y, int width, int height)
{

    graphics->render_rect(x, y, width, height);
}

void graphics_render_text(Graphics *graphics, int x, int y, char *text)
{

    graphics->render_text(x, y, text);
}

void graphics_render_point(Graphics *graphics, int x, int y)
{

    graphics->render_point(x, y);
}

void graphics_render_2_digit_int(Graphics *graphics, int x, int y, int value)
{

    char text[13];
    sprintf(text, "%d", value);

    if (value < 10)
    {
        sprintf(text, "0%d", value);
    }
    else
    {
        sprintf(text, "%d", value);
    }
    graphics_render_text(graphics, x, y, text);
}

void graphics_render_float(Graphics *graphics, int x, int y, float value)
{

    char buffer[64];
    int ret = snprintf(buffer, sizeof buffer, "%f", value);
    graphics_render_text(graphics, x, y, buffer);
}
