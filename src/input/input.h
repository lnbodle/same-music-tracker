#ifndef INPUT_H_
#define INPUT_H_

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
    Inputs inputs[8];
} Input;

int  input_get(Input* input, int input_index);
void input_set(Input* input, int input_index, int value);

#endif