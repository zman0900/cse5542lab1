#ifndef __POLYLINE_H__
#define __POLYLINE_H__

#define _USE_MATH_DEFINES
#include <cmath>
#include <list>
#include <GL/glut.h>

#include "Point.h"

#define DEF_U 0.0
#define DEF_V 0.04

class Polyline {
protected:
	std::list<Point> points;
	float colorr, colorg, colorb;
	float u, v;
	Point *prev;

	void recalcLatest();
public:
	Polyline(float x, float y, float colorr, float colorg, float colorb);
	~Polyline();

	void addPoint();
	void enlarge();
	void render();
	void rotate();
	void setColor(float colorr, float colorg, float colorb);
	void shrink();
};

#endif
