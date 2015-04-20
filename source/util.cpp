#include "util.h"

void assertS(bool condition, string errorMessage) {
    if (!condition) {
        cout << errorMessage << endl;
    }
    assert(condition);
}