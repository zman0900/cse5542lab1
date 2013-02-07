#ifndef __POLYLINE_H__
#define __POLYLINE_H__

#include <list>
#include <GL/glut.h>

#include "Point.h"

class Polyline {
protected:
	std::list<Point> points;
	float colorr, colorg, colorb;
public:
	Polyline(float x, float y, float colorr, float colorg, float colorb);
	~Polyline();

	void render();
	void setColor(float colorr, float colorg, float colorb);
};

#endif
