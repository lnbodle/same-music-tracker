SOURCES = 
SOURCES += \
src/main.c \
src/utils.c \
src/tracker/tracker.c \
src/sound/channel.c \
src/sound/filter.c \
src/sound/osc.c \
src/sound/sound.c \
src/sound/adsr.c \
src/sound/instrument.c \
src/graphics/graphics.c \
src/input/input.c \
src/views/tracker_view.c \
src/views/song_view.c \
src/views/chain_view.c \
src/views/phrase_view.c

LIBS_SOURCES =
LIBS_SOURCES += \
libs/SDL_inprint/inprint2.c  

linux:
	gcc -o bin/tracker $(SOURCES) $(LIBS_SOURCES) -lSDL2 -lm
	./bin/tracker