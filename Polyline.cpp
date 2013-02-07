#include "Polyline.h"

using namespace std;

namespace visualstudio_sucks {

void Polyline::recalcLatest() {
	if (prev != NULL) {
		Point *p = &points.back();
		p->setX(prev->getX() + u);
		p->setY(prev->getY() + v);
	}
}

void Polyline::turn(float theta) {
	float un = u * cos(theta) - v * sin(theta);
	float vn = u * sin(theta) + v * cos(theta);
	u = un;
	v = vn;
}

Polyline::Polyline(float x, float y, float _colorr, float _colorg,
                   float _colorb) {
    colorr = _colorr;
    colorg = _colorg;
    colorb = _colorb;
    u = DEF_U;
    v = DEF_V;
    prev = NULL;
	points.push_back(Point(x, y));
}

Polyline::~Polyline() {
}

void Polyline::addPoint() {
	prev = &points.back();
	points.push_back(Point(prev->getX() + u, prev->getY() + v));
}

void Polyline::addPolygon() {
	// Save u, v
	float m = u, n = v;

	u = POLYGON_SIZE;
	v = 0.0;
	for (int i = 0; i < POLYGON_SIDES; i++) {
		turn(2*M_PI/POLYGON_SIDES);
		addPoint();
	}

	// Restore u, v
	u = m; v = n;
}

void Polyline::addSpiral() {
	// Save u, v
	float m = u, n = v;

	u = SPIRAL_START_SIZE;
	v = 0.0;
	float theta = SPIRAL_START_ANGLE;
	for (int i = 0; i < SPIRAL_ITERATIONS; i++) {
		turn(theta);
		// scale
		theta *= SPIRAL_SCALE_FACTOR;
		addPoint();
	}

	// Restore u, v
	u = m; v = n;
}

void Polyline::addStar() {
	// Save u, v
	float m = u, n = v;

	u = STAR_SIZE;
	v = 0.0;
	for (int i = 0; i < STAR_SIDES; i++) {
		turn(4*M_PI/STAR_SIDES);
		addPoint();
	}

	// Restore u, v
	u = m; v = n;
}

void Polyline::enlarge() {
	u *= 1.5;
	v *= 1.5;
	recalcLatest();
}

void Polyline::render() {
	// Setup
	glColor3f(colorr, colorg, colorb);
	list<Point>::iterator it;
	glBegin(GL_LINE_STRIP);
	// Render pass 1 - lines
	for (it = points.begin(); it != points.end(); ++it) {
		(*it).render();
	}
	glEnd();
	// Render pass 2 - points
	glPointSize(5);
	glBegin(GL_POINTS);
	for (it = points.begin(); it != points.end(); ++it) {
		(*it).render();
	}
	glEnd();
}

void Polyline::rotate() {
	turn(M_PI/18);
	recalcLatest();
}

void Polyline::setColor(float _colorr, float _colorg, float _colorb) {
	colorr = _colorr;
    colorg = _colorg;
    colorb = _colorb;
}

void Polyline::shrink() {
	u *= .5;
	v *= .5;
	recalcLatest();
}

}
