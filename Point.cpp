#include "Point.h"

using namespace std;

namespace visualstudio_sucks {

Point::Point(float _x, float _y) {
	x = _x;
	y = _y;
}

Point::~Point() {
}

float Point::getX() {
	return x;
}

float Point::getY() {
	return y;
}

void Point::render() {
	glVertex2f(x, y);
}

void Point::setX(float _x) {
	x = _x;
}

void Point::setY(float _y) {
	y = _y;
}

}
