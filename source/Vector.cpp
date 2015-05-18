#include "Vector.h"

Vector::Vector(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector::add(Vector* v2) {
    this->x += v2->x;
    this->y += v2->y;
    this->z += v2->z;
}

void Vector::printInfo() {
    cout << "(" << this->x << ", " << this->y << ", " << this->z << ")" << endl;
}

void Vector::multiply(Vector* v2) {
    this->x *= v2->x;
    this->y *= v2->y;
    this->z *= v2->z;
}
