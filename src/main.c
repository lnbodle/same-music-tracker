#include "SDL2/SDL.h"
#include <stdio.h>

#include "sound_engine/sound_engine.h"
#include "tracker_engine/tracker_engine.h"
#include "ui_engine/ui_engine.h"

#include "common.h"

SDL_AudioCallback callback;
SDL_AudioDeviceID audio_device;
SDL_AudioSpec audio_spec;

SDL_Renderer *renderer;

SoundEngine sound_engine;
TrackerEngine tracker_engine;
UiEngine ui_engine;

int audio_buffer_size;
float audio_buffer[SAMPLES];

void audio_callback(void *audio, Uint8 *stream, int len) {
    
    tracker_engine_cycle(&tracker_engine);

    float *buffer = (float *)stream;

    for (int index = 0; index < len / sizeof(float); index++)
    {
        buffer[index] = sound_engine_cycle(&sound_engine);
    }
}

void render_rect_callback(int x, int y, int width, int height) {

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
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

    //Audio
    SDL_zero(audio_spec);
    audio_spec.freq = SAMPLE_RATE;
    audio_spec.format = AUDIO_F32;
    audio_spec.channels = 1;
    audio_spec.samples = SAMPLES;
    audio_spec.callback = audio_callback;
    audio_spec.userdata = NULL;

    audio_device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0, 0), 0, &audio_spec, NULL, 0);

    SDL_PauseAudioDevice(audio_device, 0);

    sound_engine_init(&sound_engine);
    tracker_engine_init(&tracker_engine, &sound_engine);

    ui_engine.sound_engine = &sound_engine;
    ui_engine.tracker_engine = &tracker_engine;
    ui_engine.render_rect = render_rect_callback;

    int quit = 0;
    SDL_Event e;

    while (!quit)
    {
        SDL_RenderClear(renderer);
        SDL_RenderFillRect(renderer, NULL);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        ui_engine_render(&ui_engine);
        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }

        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}