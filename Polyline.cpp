#include "Polyline.h"

using namespace std;

Polyline::Polyline(float x, float y, float _colorr, float _colorg,
                   float _colorb) {
    colorr = _colorr;
    colorg = _colorg;
    colorb = _colorb;
	points.push_back(Point(x, y));
}

Polyline::~Polyline() {
}

void Polyline::render() {
	glColor3f(colorr, colorg, colorb);
	// Render first point
	list<Point>::iterator it = points.begin();
	(*it).render();
	// Render any additional points with connecting lines
	for (;it != points.end(); ++it) {
		
	}
}

void Polyline::setColor(float _colorr, float _colorg, float _colorb) {
	colorr = _colorr;
    colorg = _colorg;
    colorb = _colorb;
}
