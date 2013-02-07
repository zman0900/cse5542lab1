#include "Point.h"

using namespace std;

Point::Point(float _x, float _y) {
	x = _x;
	y = _y;
}

Point::~Point() {
}

void Point::render() {
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}
