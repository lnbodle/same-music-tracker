#include <math.h> 
#include <stdio.h>
#include "utils.h"

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

int clamp_int(int d, int min, int max) {
  const int t = d < min ? min : d;
  return t > max ? max : t;
}

float clamp_float(float d, float min, float max) {
  const float t = d < min ? min : d;
  return t > max ? max : t;
}

double distance(int x1, int y1, int x2, int y2)
{
    int x_diff = x2 - x1;
    int y_diff = y2 - y1;
    double distance = sqrt((x_diff * x_diff) + (y_diff * y_diff));
    return distance;
}