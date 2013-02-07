#include "Polyline.h"

using namespace std;

void Polyline::recalcLatest() {
	if (prev != NULL) {
		Point *p = &points.back();
		p->setX(prev->getX() + u);
		p->setY(prev->getY() + v);
	}
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
	float un, vn;
	un = u * cos(M_PI/18) - v * sin(M_PI/18);
	vn = u * sin(M_PI/18) + v * cos(M_PI/18);
	u = un;
	v = vn;
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
