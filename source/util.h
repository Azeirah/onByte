#pragma once

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)
#define assertS(truthy, message) if (!(truthy)) {cout << message << " on line " << __LINE__ << " in file " << __FILE__ << ". Check was " << #truthy << endl;}

float generateFloat(float, float);
float translate(float in, float min, float max, float newMin, float newMax);
