#include "json/json.h"
#include <iostream>

using namespace std;

int main() {
    Json::Value root;
    Json::Value &leaf = root["b"];

    leaf = 5;
    cout << root.toStyledString() << endl;

    leaf = "beats";
    cout << root.toStyledString() << endl;

    return 0;
}
