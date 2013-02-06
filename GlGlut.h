#ifndef __GLGLUT_H__
#define __GLGLUG_H__

#include <cstdlib>
#include <iostream>

#include <GL/glut.h>

#define DEF_SCREEN_W 800
#define DEF_SCREEN_H 800
#define WINDOW_TITLE "CSE 5542 Lab 1 - Dan Ziemba"
#define TRANSLATE_FACTOR 0.2
#define ZOOM_FACTOR 1.5

class GlGlut {
protected:
	static GlGlut *instance;
	int screen_width;
	int screen_height;
	float translate_factor;
	float zoom_factor;
	
	// Glut callbacks
	void display();
	void idle();
	void keyboard(unsigned char key, int mousex, int mousey);
	void mouseClick(int button, int state, int x, int y);
	void mouseMove(int x, int y);
	void reshape(int w, int h);
	void special(int key, int mousex, int mousey);

	////  Static wrappers used to register glut callbacks
	static void displayWrapper();
	static void idleWrapper();
	static void keyboardWrapper(unsigned char key, int mousex, int mousey);
	static void mouseClickWrapper(int button, int state, int x, int y);
	static void mouseMoveWrapper(int x, int y);
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

#endif
