#ifndef __GLGLUT_H__
#define __GLGLUG_H__

#include <cstdlib>
#include <iostream>
#include <list>

#include <GL/glut.h>

#include "Polyline.h"

#define DEF_SCREEN_W 800
#define DEF_SCREEN_H 800
#define WINDOW_TITLE "CSE 5542 Lab 1 - Dan Ziemba"
#define TRANSLATE_FACTOR 0.2
#define ZOOM_FACTOR 1.5

namespace visualstudio_sucks {

class GlGlut {
private:
	void deviceCoordToViewPort(int &x, int &y);
	void deviceToWorldCoord(float &x, float &y);
protected:
	static GlGlut *instance;
	int screen_width;
	int screen_height;
	int menu_visible;
	float translate_factor;
	float zoom_factor;
	float colorr, colorb, colorg;
	std::list<Polyline> lines;

	static const int MENU_WHITE = 0;
	static const int MENU_RED = 1;
	static const int MENU_GREEN = 2;
	static const int MENU_BLUE = 3;

	void buildMenu();
	
	// Glut callbacks
	void display();
	void idle();
	void keyboard(unsigned char key, int mousex, int mousey);
	void menuClick(int value);
	void menuStatus(int status, int x, int y);
	void mouseClick(int button, int state, int x, int y);
	void reshape(int w, int h);
	void special(int key, int mousex, int mousey);

	////  Static wrappers used to register glut callbacks
	static void displayWrapper();
	static void idleWrapper();
	static void keyboardWrapper(unsigned char key, int mousex, int mousey);
	static void menuClickWrapper(int value);
	static void menuStatusWrapper(int status, int x, int y);
	static void mouseClickWrapper(int button, int state, int x, int y);
	static void reshapeWrapper(int w, int h);
	static void specialWrapper(int key, int mousex, int mousey);
public:
	GlGlut();
	~GlGlut();

	// Called by start to make wrappers work
	void setInstance();
	// Starts scene, does not return
	void start(int *argc, char *argv[]);
};

}

#endif
