#include "../sound_engine/sound_engine.h"
#include "../tracker_engine/tracker_engine.h"

typedef struct {

    SoundEngine *sound_engine;
    TrackerEngine *tracker_engine;

    void (*render_rect)(int x, int y, int width, int height);
    void (*render_text)(int x, int y, char* string);
    void (*render_point)(int x, int y);

} UiEngine;

void ui_engine_render_rect(UiEngine *ui_engine, int x, int y, int width, int height);
void ui_engine_render_text(UiEngine *ui_engine, int x, int y, char *string);
void ui_engine_render_point(UiEngine *ui_engine, int x, int y);
void ui_engine_render_waveform(UiEngine *ui_engine,int x, int y, int width, int height, float *buffer, int buffer_size);
void ui_engine_render_phrase(UiEngine *ui_engine);

void ui_engine_render(UiEngine *ui_engine);