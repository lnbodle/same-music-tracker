#include "control.h"

void control_event(Control *control) {

    if (control->inputs[Left]) {
        control->tracker->song_x -= 1;
    }

    if (control->inputs[Right]) {
        
        control->tracker->song_x += 1;
    }
}

void control_set_value(Control* control, int input, int value) {

    control->inputs[input] = value;
}