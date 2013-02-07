#ifndef __POINT_H__
#define __POINT_H__

#include <GL/glut.h>

class Point {
protected:
	float x, y;
public:
	Point(float x, float y);
	~Point();

	float getX();
	float getY();
	void render();
	void setX(float x);
	void setY(float y);
};

#endif
