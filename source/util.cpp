#include "util.h"

void assertS(bool condition, string errorMessage) {
    if (!condition) {
        cout << "assertion warning: " << errorMessage << endl;
    }
}

float generateFloat(float low, float high) {
    return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(high-low)));
}
