#ifndef __POLYLINE_H__
#define __POLYLINE_H__

#define _USE_MATH_DEFINES
#include <cmath>
#include <list>
#include <GL/glut.h>

#include "Point.h"

#define DEF_U 0.0
#define DEF_V 0.04
#define POLYGON_SIDES 5
#define POLYGON_SIZE 0.5
#define STAR_SIDES 5
#define STAR_SIZE 0.5
#define SPIRAL_START_SIZE 0.05
#define SPIRAL_START_ANGLE (M_PI/2)
#define SPIRAL_SCALE_FACTOR 0.95
#define SPIRAL_ITERATIONS 40

class Polyline {
protected:
	std::list<Point> points;
	float colorr, colorg, colorb;
	float u, v;
	Point *prev;

	void recalcLatest();
	void turn(float theta);
public:
	Polyline(float x, float y, float colorr, float colorg, float colorb);
	~Polyline();

	void addPoint();
	void addPolygon();
	void addSpiral();
	void addStar();
	void enlarge();
	void render();
	void rotate();
	void setColor(float colorr, float colorg, float colorb);
	void shrink();
};

#endif
