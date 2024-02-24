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
src/ui/ui.c \
src/control/control.c

LIBS_SOURCES =
LIBS_SOURCES += \
libs/SDL_inprint/inprint2.c  

linux:
	gcc -o bin/tracker $(SOURCES) $(LIBS_SOURCES) -lSDL2 -lm
	./bin/tracker