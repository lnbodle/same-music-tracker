#include "SDL2/SDL.h"
#include <stdio.h>

#include "../libs/SDL_inprint/SDL2_inprint.h"

#include "sound/sound.h"
#include "tracker/tracker.h"
#include "ui/ui.h"
#include "control/control.h"

#include "common.h"

SDL_AudioCallback callback;
SDL_AudioDeviceID audio_device;
SDL_AudioSpec audio_spec;

SDL_Renderer *renderer;

Sound sound;
Tracker tracker;
Ui ui;
Control control;

int audio_buffer_size;
float audio_buffer[SAMPLES];

void audio_callback(void *audio, Uint8 *stream, int len)
{

    tracker_cycle(&tracker);

    float *buffer = (float *)stream;

    for (int index = 0; index < len / sizeof(float); index++)
    {
        buffer[index] = sound_cycle(&sound);
    }
}

void render_rect_callback(int x, int y, int width, int height)
{

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
}

void render_text_callback(int x, int y, char *text)
{

    incolor(0xFF0000, 0x333333);
    inprint(renderer, text, x, y);
}

int main(int argc, char *argv[])
{
    int sdl_init = SDL_Init(SDL_INIT_EVERYTHING);
    if (sdl_init)
    {
        printf("SDL can't be initalize");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("TRACKER", 128, 128, 640, 480, 0);
    if (window == NULL)
    {
        printf("SDL_Window can't be initalize");
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0 /* SDL_RENDERER_TARGETTEXTURE*/);
    if (renderer == NULL)
    {
        printf("SDL_Render can't be initalize");
        return 1;
    }

    // Audio
    SDL_zero(audio_spec);
    audio_spec.freq = SAMPLE_RATE;
    audio_spec.format = AUDIO_F32;
    audio_spec.channels = 1;
    audio_spec.samples = SAMPLES;
    audio_spec.callback = audio_callback;
    audio_spec.userdata = NULL;

    audio_device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0, 0), 0, &audio_spec, NULL, 0);

    SDL_PauseAudioDevice(audio_device, 0);

    sound_init(&sound);
    tracker_init(&tracker, &sound);

    ui.sound = &sound;
    ui.tracker = &tracker;
    ui.render_rect = render_rect_callback;
    ui.render_text = render_text_callback;
    ui.font_width = 8;
    ui.font_height = 8;

    control.tracker = &tracker;

    inrenderer(renderer);
    prepare_inline_font();

    int quit = 0;
    SDL_Event e;

    while (!quit)
    {
        SDL_RenderClear(renderer);
        SDL_RenderFillRect(renderer, NULL);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        ui_render(&ui);

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }

            if (e.type == SDL_KEYDOWN)
            {
                SDL_Keycode keycode = e.key.keysym.sym;

                switch (keycode)
                {

                case SDLK_LEFT:
                    control_set_value(&control, Left, 1);
                    break;

                case SDLK_RIGHT:
                    control_set_value(&control, Right, 1);
                    break;

                case SDLK_UP:
                    control_set_value(&control, Up, 1);
                    break;

                case SDLK_DOWN:
                    control_set_value(&control, Down, 1);
                    break;
                }
                control_event(&control);
            }

            if (e.type == SDL_KEYUP)
            {
                SDL_Keycode keycode = e.key.keysym.sym;
                switch (keycode)
                {

                case SDLK_LEFT:
                    control_set_value(&control, Left, 0);
                    break;

                case SDLK_RIGHT:
                    control_set_value(&control, Right, 0);
                    break;

                case SDLK_UP:
                    control_set_value(&control, Up, 0);
                    break;

                case SDLK_DOWN:
                    control_set_value(&control, Down, 0);
                    break;
                }
            }
        }
    }

    kill_inline_font();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}