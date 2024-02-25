#ifndef INPUT_H_
#define INPUT_H_

#include "../tracker/tracker.h"

typedef enum {
    Up,
    Down,
    Left,
    Right,
    Option,
    Edit,
    Shift,
    Play
} Inputs;

typedef struct {

    Tracker *tracker;
    Inputs inputs[7];
} Input;

int  input_get(Input* input, int input_index);
void input_set(Input* input, int input_index, int value);

#endif