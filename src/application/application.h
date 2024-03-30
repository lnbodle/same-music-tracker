#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "../instrument/instrument.h"
#include "../common.h"
#include "../sound/sound.h"
#include "../graphics/graphics.h"
#include "../input/input.h"

typedef enum
{
    VIEW_SONG,
    VIEW_CHAIN,
    VIEW_PHRASE,
    VIEW_INSTRUMENT,
    VIEW_ENVELOPES
} Views;

typedef struct {

    int note;
    int octave;
    int instrument;
} Step;

typedef struct
{
    Sound sound;
    Graphics graphics;
    Input input;

    int current_view_indice;

    int cursor_x;
    int cursor_y;

    int font_width;
    int font_height;
    int padding;

    Instrument instruments[4];

    float tick;
    float tempo;

    int playing_step;
    int playing_phrase;
    int playing_chains;

    int selected_phrase;
    int selected_chain;
    int selected_step;
    int selected_instrument;

    int playing;

    int song[TRACK_SIZE][SONG_SIZE];
    int chains[CHAIN_SIZE][PHRASE_PER_CHAIN];

    Step phrases[PHRASE_SIZE][STEP_PER_PHRASE];
} Application;

void application_init(Application *application, void *render_rect_callback, void *render_text_callback);
void application_input(Application *application);
void application_cycle(Application *application);
void application_render(Application *application);
void application_reset_cursor(Application *application);
void application_free(Application *application);

void application_add_parameter(Application *app, int index, Parameter input);
void application_render_parameter(Application *app, int index, int check);
int get_nearest_parameter(Application *app, Parameter *input, int check);

#endif