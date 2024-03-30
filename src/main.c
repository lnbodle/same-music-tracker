#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "application/application.h"
#include "common.h"
#include "utils.h"

#define KEY_UP SDLK_w
#define KEY_DOWN SDLK_s
#define KEY_LEFT SDLK_q
#define KEY_RIGHT SDLK_d
#define KEY_A SDLK_a
#define KEY_B SDLK_b
#define KEY_R SDLK_l
#define KEY_L SDLK_h
#define KEY_Y SDLK_y
#define KEY_X SDLK_x
#define KEY_MENU SDLK_u
#define KEY_SELECT SDLK_n
#define KEY_START SDLK_m
#define KEY_L2 SDLK_j
#define KEY_R2 SDLK_k

SDL_AudioSpec *desired, *obtained;
SDL_AudioSpec *hardware_spec;

SDL_Surface *screen;

Application app;

TTF_Font *font;
SDL_Surface *textSurface;

int audio_buffer_size;
float audio_buffer[SAMPLES];

void audio_callback(void *audio, Uint8 *stream, int len)
{
  application_cycle(&app);

  int *buffer = (int *)stream;

  for (int index = 0; index < len / sizeof(int); index++)
  {

    int sample = (int)(sound_cycle(&app.sound) * 32767.0f);
    buffer[index] = sample;
  }
}

void render_rect_callback(int x, int y, int width, int height)
{
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = width;
  rect.h = height;
  SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 100, 100, 100));
}

void draw_text(int x, int y, char *text)
{
  SDL_Color font_color = {255, 255, 255};
  SDL_Rect font_rect;
  textSurface = TTF_RenderText_Blended(font, text, font_color);
  font_rect.x = x;
  font_rect.y = y;
  SDL_BlitSurface(textSurface, NULL, screen, &font_rect);
  SDL_FreeSurface(textSurface);
}

void render_text_callback(int x, int y, char *text)
{
  draw_text(x, y, text);
}

int main(int argc, char *argv[])
{
  setenv("SDL_NOMOUSE", "1", 1);

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    const char *Error = SDL_GetError();
    printf("SDL_Init error %s\n", Error);
    return 0;
  }

  SDL_ShowCursor(0);

  int r = SDL_VideoModeOK(640, 480, 16, SDL_HWSURFACE);
  if (r == 0)
  {
    printf("Unable to set video mode: %s\n", SDL_GetError());
    return 1;
  }

  screen = SDL_SetVideoMode(640, 480, 16, 0);
  if (screen == NULL)
  {
    printf("Unable to set video mode: %s\n", SDL_GetError());
    return 1;
  }

  if (TTF_Init() != 0)
  {
    fprintf(stderr, "TTF Init error...\n");
    return 0;
  }

  font = TTF_OpenFont("assets/font.ttf", 24);
  if (!font)
  {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
  }

  desired = malloc(sizeof(SDL_AudioSpec));
  obtained = malloc(sizeof(SDL_AudioSpec));

  desired->freq = SAMPLE_RATE;
  desired->format = AUDIO_S16SYS;
  desired->channels = 1;
  desired->samples = SAMPLES;
  desired->callback = audio_callback;
  desired->userdata = NULL;

  /* Open the audio device */
  if (SDL_OpenAudio(desired, obtained) < 0)
  {
    fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
    exit(-1);
  }

  free(desired);
  hardware_spec = obtained;

  SDL_PauseAudio(0);

  application_init(&app, render_rect_callback, render_text_callback);
  app.graphics.render_rect = render_rect_callback;
  app.graphics.render_text = render_text_callback;

  int quit = 0;
  SDL_Event e;

  while (!quit)
  {
    SDL_FillRect(screen, NULL, 0x000000);

    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        quit = 1;
      }

      if (e.type == SDL_KEYDOWN)
      {
        if (e.key.keysym.sym == KEY_MENU)
        {
          quit = 1;
        }

        switch (e.key.keysym.sym)
        {

        case KEY_LEFT:
          input_set(&app.input, Left, 1);
          break;

        case KEY_RIGHT:
          input_set(&app.input, Right, 1);
          break;

        case KEY_UP:
          input_set(&app.input, Up, 1);
          break;

        case KEY_DOWN:
          input_set(&app.input, Down, 1);
          break;

        case KEY_START:
          input_set(&app.input, Play, 1);
          break;

        case KEY_SELECT:
          input_set(&app.input, Shift, 1);
          break;

        case KEY_B:
          input_set(&app.input, Option, 1);
          break;

        case KEY_A:
          input_set(&app.input, Edit, 1);
          break;
        }

        application_input(&app);
      }

      if (e.type == SDL_KEYUP)
      {

        switch (e.key.keysym.sym)
        {

        case KEY_LEFT:
          input_set(&app.input, Left, 0);
          break;

        case KEY_RIGHT:
          input_set(&app.input, Right, 0);
          break;

        case KEY_UP:
          input_set(&app.input, Up, 0);
          break;

        case KEY_DOWN:
          input_set(&app.input, Down, 0);
          break;

        case KEY_START:
          input_set(&app.input, Play, 0);
          break;

        case KEY_SELECT:
          input_set(&app.input, Shift, 0);
          break;

        case KEY_B:
          input_set(&app.input, Option, 0);
          break;

        case KEY_A:
          input_set(&app.input, Edit, 0);
          break;
        }
      }
    }

    application_render(&app);
    SDL_Flip(screen);
  }

  SDL_FreeSurface(screen);
  TTF_CloseFont(font);
  SDL_Quit();

  return 0;
}