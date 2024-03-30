#define FREQ_TAB_SIZE 12 /* one octave */

float note_to_frequency(int note);
int increase_index(int index, int size);
int decrease_index(int index, int size);

int clamp_int(int d,int min,int max);
float clamp_float(float d, float min, float max);

double distance(int x1, int y1, int x2, int y2);