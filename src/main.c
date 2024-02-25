#include "SDL2/SDL.h"
#include <stdio.h>

#include "../libs/SDL_inprint/SDL2_inprint.h"
#include "sound/sound.h"
#include "tracker/tracker.h"
#include "graphics/graphics.h"
#include "input/input.h"
#include "views/tracker_view.h"
#include "common.h"

SDL_AudioCallback callback;
SDL_AudioDeviceID audio_device;
SDL_AudioSpec audio_spec;
SDL_Renderer *renderer;

Sound sound;
Tracker tracker;
Graphics graphics;
Input input;
TrackerView tracker_view;

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
    incolor(0xFFFFFF, 0x333333);
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

    graphics.render_rect = render_rect_callback;
    graphics.render_text = render_text_callback;
    graphics.font_width = 8;
    graphics.font_height = 8;

    tracker_view_init(&tracker_view, &tracker, &graphics, &input);

    inrenderer(renderer);
    prepare_inline_font();

    int quit = 0;
    SDL_Event e;

    while (!quit)
    {
        SDL_RenderClear(renderer);
        SDL_RenderFillRect(renderer, NULL);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        tracker_view_render(&tracker_view);

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
                    input_set(&input, Left, 1);
                    break;

                case SDLK_RIGHT:
                    input_set(&input, Right, 1);
                    break;

                case SDLK_UP:
                    input_set(&input, Up, 1);
                    break;

                case SDLK_DOWN:
                    input_set(&input, Down, 1);
                    break;

                case SDLK_SPACE:
                    input_set(&input, Play, 1);
                    break;

                case SDLK_LSHIFT:
                    input_set(&input, Shift, 1);
                    break;

                case SDLK_a:
                    input_set(&input, Option, 1);
                    break;

                case SDLK_z:
                    input_set(&input, Edit, 1);
                    break;
                }

                tracker_view_input(&tracker_view);
            }

            if (e.type == SDL_KEYUP)
            {
                SDL_Keycode keycode = e.key.keysym.sym;
                switch (keycode)
                {

                case SDLK_LEFT:
                    input_set(&input, Left, 0);
                    break;

                case SDLK_RIGHT:
                    input_set(&input, Right, 0);
                    break;

                case SDLK_UP:
                    input_set(&input, Up, 0);
                    break;

                case SDLK_DOWN:
                    input_set(&input, Down, 0);
                    break;

                case SDLK_SPACE:
                    input_set(&input, Play, 0);
                    break;

                case SDLK_LSHIFT:
                    input_set(&input, Shift, 0);
                    break;

                case SDLK_a:
                    input_set(&input, Option, 0);
                    break;
                    
                case SDLK_z:
                    input_set(&input, Edit, 0);
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