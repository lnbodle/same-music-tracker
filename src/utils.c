#include <math.h> 
#include <stdio.h>

float note_to_frequency(int note) {
    float a = 440; //frequency of A (coomon value is 440Hz)
    return (a / 32) * pow(2, ((note - 9) / 12.0));
}

int increase_index(int index, int size)
{

    if (index >= size - 1)
    {
        index = 0;
    }
    else
    {
        index++;
    }

    return index;
}

int decrease_index(int index, int size)
{
    if (index <= 0)
    {
        index = size - 1;
    }
    else
    {
        index--;
    }
    
    return index;
}