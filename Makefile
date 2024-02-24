SOURCES = 
SOURCES += \
src/main.c \
src/utils.c \
src/tracker_engine/tracker_engine.c \
src/sound_engine/channel.c \
src/sound_engine/filter.c \
src/sound_engine/osc.c \
src/sound_engine/sound_engine.c \
src/sound_engine/adsr.c \
src/ui_engine/ui_engine.c

linux:
	gcc -o bin/tracker $(SOURCES) -lSDL2 -lm
	./bin/tracker