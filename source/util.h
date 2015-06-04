#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

#define assertS(truthy, message) if (!(truthy)) {cout << message << " on line " << __LINE__ << " in file " << __FILE__ << endl;}

float generateFloat(float, float);
