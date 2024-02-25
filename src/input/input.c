#include "input.h"

int input_get(Input *input, int input_index)
{
    return input->inputs[input_index];
}

void input_set(Input *input, int input_index, int value)
{
    input->inputs[input_index] = value;
}