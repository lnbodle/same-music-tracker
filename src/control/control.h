#ifndef CONTROL_H_
#define CONTROL_H_

#include "../tracker/tracker.h"

typedef enum {
    Up,
    Down,
    Left,
    Right
} Inputs;

typedef struct {

    Tracker *tracker;
    Inputs inputs[4];
} Control;

void control_event(Control *control);
void control_set_value(Control* control, int input, int value);

#endif