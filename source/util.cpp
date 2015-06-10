#include "util.h"

float generateFloat(float low, float high) {
    return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(high-low)));
}

float translate(float in, float min, float max, float newMin, float newMax) {
    float leftSpan = max - min;
    float rightSpan = newMax - newMin;
    float scaled = (in - min) / leftSpan;

    return newMin + scaled * rightSpan;
}
