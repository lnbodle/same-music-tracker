#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "../sound/sound.h"
#include "../tracker/tracker.h"

typedef struct {

    int font_width;
    int font_height;

    void (*render_rect)(int x, int y, int width, int height);
    void (*render_text)(int x, int y, char *string);
    void (*render_point)(int x, int y);

} Graphics;

void graphics_render_rect(Graphics *graphics, int x, int y, int width, int height);
void graphics_render_text(Graphics *graphics, int x, int y, char *string);
void graphics_render_point(Graphics *graphics, int x, int y);
void graphics_render_2_digit_int(Graphics *graphics, int x, int y, int value);

#endif