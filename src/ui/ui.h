#ifndef UI_H_
#define UI_H_

#include "../sound/sound.h"
#include "../tracker/tracker.h"

typedef struct {

    Sound *sound;
    Tracker *tracker;

    int font_width;
    int font_height;

    void (*render_rect)(int x, int y, int width, int height);
    void (*render_text)(int x, int y, char *string);
    void (*render_point)(int x, int y);

} Ui;

void ui_render_rect(Ui *ui, int x, int y, int width, int height);
void ui_render_text(Ui *ui, int x, int y, char *string);
void ui_render_point(Ui *ui, int x, int y);
void ui_render_waveform(Ui *ui,int x, int y, int width, int height, float *buffer, int buffer_size);
void ui_render_phrase(Ui *ui);

void ui_render(Ui *ui);

#endif