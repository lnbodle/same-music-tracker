#include <stdlib.h>

#include "ui.h"

void ui_render_rect(Ui *ui, int x, int y, int width, int height)
{

    ui->render_rect(x, y, width, height);
}

void ui_render_text(Ui *ui, int x, int y, char *text)
{

    ui->render_text(x, y, text);
}

void ui_render_point(Ui *ui, int x, int y)
{

    ui->render_point(x, y);
}

void ui_render_waveform(Ui *ui, int x, int y, int width, int height, float *buffer, int buffer_size)
{

    for (int i = 0; i < width; i++)
    {
        int remaped_index = (buffer_size / width) * i;

        int middle = y + (height / 2);
        float range = buffer[remaped_index] * (height * 2);

        ui_render_point(ui, x + i, middle + range);
    }
}

void ui_render_song(Ui *ui)
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {

            char c[2];
            sprintf(c, "%d", ui->tracker->song[i][j]);
            ui_render_text(ui, i * ui->font_width * 2, j * ui->font_height, c);
        }
    }

    ui_render_rect(ui, 16 + ui->tracker->song_x * 16, 16, 8, 8);
}

void ui_render_phrase(Ui *ui)
{

    ui_render_song(ui);

    for (int i = 0; i < 16; i++)
    {

        /*Step step = ui->tracker_engine->current_song.chains[0].phrases[0].steps[i];
        ui_render_rect(ui 16 , 16 + i * 16, (step.note - 64) * 8, 8);*/
    }

    int current_step_index = ui->tracker->current_step_index;
    ui_render_rect(ui, 16, 16 + current_step_index * 16, 8, 8);
}

void ui_render(Ui *ui)
{

    ui_render_song(ui);

    // ui_render_phrase(ui);
}