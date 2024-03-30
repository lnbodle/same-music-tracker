# tracker - simple terminal
# See LICENSE file for copyright and license details.

include config.mk

SRC =
SRC += \
src/main.c \
src/utils.c \
src/sound/channel.c \
src/sound/sound.c \
src/sound/envelope.c \
src/graphics/graphics.c \
src/input/input.c \
src/views/song_view.c \
src/views/phrase_view.c \
src/views/envelopes_view.c \
src/views/instrument_view.c \
src/application/application.c \
src/sound/osc.c \
src/sound/adsr.c \
src/sound/filter.c \
src/sound/sampler.c \
src/instrument/instrument.c \
libs/tinywav/tinywav.c

OBJ = ${SRC:.c=.o}

all: options tracker 

options:
	@echo tracker build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo $(CC) $<
	@${CC} -c ${CFLAGS} $<

tracker: 
	@echo $(CC) -o $@
	@${CC} -o bin/$@ ${SRC} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f tracker ${OBJ}

.PHONY: all options clean
