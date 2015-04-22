#include "util.h"

void assertS(bool condition, string errorMessage) {
    if (!condition) {
        cout << "assertion warning: " << errorMessage << endl;
    }
}
