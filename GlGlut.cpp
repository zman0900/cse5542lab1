#include "GlGlut.h"

GlGlut *GlGlut::instance = NULL;

GlGlut::GlGlut() {
	screen_width = DEF_SCREEN_W;
	screen_height = DEF_SCREEN_H;
}

GlGlut::~GlGlut() {
	// Nothing to do here
}

void GlGlut::start(int *argc, char *argv[]) {
	setInstance();

	// Init glut
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(screen_width, screen_height);
	glutCreateWindow(WINDOW_TITLE);

	// Register callbacks
	glutDisplayFunc(displayWrapper);

	// Start
	glutMainLoop();
}

void GlGlut::display() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glutSwapBuffers();
}

void GlGlut::reshape(int w, int h) {
	
}

void GlGlut::setInstance() {
	instance = this;
}

//// Static wrappers
void GlGlut::displayWrapper() {
	instance->display();
}

void GlGlut::reshapeWrapper(int w, int h) {
	instance->reshape(w, h);
}
