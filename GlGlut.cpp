#include "GlGlut.h"

using namespace std;

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
	glutKeyboardFunc(keyboardWrapper);
	glutMouseFunc(mouseClickWrapper);
	glutMotionFunc(mouseMoveWrapper);
	glutReshapeFunc(reshapeWrapper);

	// Start
	glutIdleFunc(idleWrapper);
	glutMainLoop();
}

//// Glut callbacks /////
void GlGlut::display() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glutSwapBuffers();
}

void GlGlut::idle() {

}

void GlGlut::keyboard(unsigned char key, int mousex, int mousey) {
	cout << "key: " << (int) key << endl;
}

void GlGlut::mouseClick(int button, int state, int x, int y) {
	cout << "click b:" << button << " x:" << x << " y:" << y << endl;
}

void GlGlut::mouseMove(int x, int y) {
	cout << "move x:" << x << " y:" << y << endl;
}

void GlGlut::reshape(int w, int h) {
	
}
/////////////////////////

void GlGlut::setInstance() {
	instance = this;
}

//// Static wrappers ////
void GlGlut::displayWrapper() {
	instance->display();
}

void GlGlut::idleWrapper() {
	instance->idle();
}

void GlGlut::keyboardWrapper(unsigned char key, int mousex, int mousey) {
	instance->keyboard(key, mousex, mousey);
}

void GlGlut::mouseClickWrapper(int button, int state, int x, int y) {
	instance->mouseClick(button, state, x, y);
}

void GlGlut::mouseMoveWrapper(int x, int y) {
	instance->mouseMove(x, y);
}

void GlGlut::reshapeWrapper(int w, int h) {
	instance->reshape(w, h);
}
/////////////////////////
