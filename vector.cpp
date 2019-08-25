#include"vector.h"

Vector2::Vector2() {
	x = 0, y = 0;
}

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

const Vector2 Vector2::Zero(0, 0);