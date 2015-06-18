#include "Vector.h"

Vector::Vector(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector* Vector::add(Vector* v2) {
    this->x += v2->x;
    this->y += v2->y;
    this->z += v2->z;

    return this;
}

void Vector::printInfo() {
    cout << "(" << this->x << ", " << this->y << ", " << this->z << ")" << endl;
}

Vector* Vector::multiply(Vector* v2) {
    this->x *= v2->x;
    this->y *= v2->y;
    this->z *= v2->z;

    return this;
}

Vector* Vector::scale(float scale) {
    this->x *= scale;
    this->y *= scale;
    this->z *= scale;

    return this;
}

Vector* Vector::clone(Vector* v) {
    this->x = v->x;
    this->y = v->y;
    this->z = v->z;

    return this;
}
