#ifndef __POINT_H__
#define __POINT_H__

#include <GL/glut.h>

class Point {
protected:
	float x, y;
public:
	Point(float x, float y);
	~Point();

	void render();
};

#endif
