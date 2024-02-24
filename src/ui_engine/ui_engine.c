#include "ui_engine.h"

void ui_engine_render_rect(UiEngine *ui_engine, int x, int y, int width, int height) {

    ui_engine->render_rect(x,y,width,height);
}

void ui_engine_render_text(UiEngine *ui_engine, int x, int y, char* text) {

    ui_engine->render_text(x,y,text);
}

void ui_engine_render_point(UiEngine *ui_engine, int x, int y) {

    ui_engine->render_point(x,y);
}

void ui_engine_render_waveform(UiEngine *ui_engine,int x, int y, int width, int height, float *buffer, int buffer_size) {

    for (int i = 0; i < width; i++)
    {
        int remaped_index = (buffer_size / width) * i;

        int middle = y + (height / 2);
        float range = buffer[remaped_index] * (height * 2);

        ui_engine_render_point(ui_engine, x + i, middle + range);
    }
}

void ui_engine_render_phrase(UiEngine *ui_engine) {

    for (int i = 0 ; i < 16 ; i++) {

        /*Step step = ui_engine->tracker_engine->current_song.chains[0].phrases[0].steps[i];
        ui_engine_render_rect(ui_engine, 16 , 16 + i * 16, (step.note - 64) * 8, 8);*/
    }

    int current_step_index = ui_engine->tracker_engine->current_step_index;
    ui_engine_render_rect(ui_engine, 16 , 16 + current_step_index * 16, 8, 8);
}

void ui_engine_render(UiEngine *ui_engine) {

    ui_engine_render_phrase(ui_engine);
}