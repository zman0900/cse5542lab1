#include "GlGlut.h"

using namespace std;

GlGlut *GlGlut::instance = NULL;

//// Glut callbacks /////
void GlGlut::display() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glRectf(-.5, -.5, .5, .5);

	glutSwapBuffers();
}

void GlGlut::idle() {

}

void GlGlut::keyboard(unsigned char key, int mousex, int mousey) {
	switch(key) {
		case 3:  // Ctrl-c
		case 27: // Esc
			exit(EXIT_SUCCESS);
			break;
		case 'a':
			glScalef(zoom_factor, zoom_factor, 1.);
			translate_factor *= 1./zoom_factor;
			glutPostRedisplay();
			break;
		case 'z':
			glScalef(1./zoom_factor, 1./zoom_factor, 1.);
			translate_factor *= zoom_factor;
			glutPostRedisplay();
			break;
		case 'q':
			glLoadIdentity();
			translate_factor = TRANSLATE_FACTOR;
			zoom_factor = ZOOM_FACTOR;
			glutPostRedisplay();
			break;
		default:
			cout << "unused key: " << (int) key << endl;
			break;
	}
}

void GlGlut::mouseClick(int button, int state, int x, int y) {
	cout << "click b:" << button << " x:" << x << " y:" << y << endl;
}

void GlGlut::mouseMove(int x, int y) {
	cout << "move x:" << x << " y:" << y << endl;
}

void GlGlut::reshape(int w, int h) {
	screen_width = w;
	screen_height = h;

	if (w > h) {
		glViewport((w-h)/2, 0, h, h);
	} else {
		glViewport(0, (h-w)/2, w, w);
	}

	glutPostRedisplay();
}

void GlGlut::special(int key, int mousex, int mousey) {
	switch (key) {
		case GLUT_KEY_LEFT:
			glTranslatef(-1.*translate_factor, 0., 0.);
			break;
		case GLUT_KEY_RIGHT:
			glTranslatef(translate_factor, 0., 0.);
			break;
		case GLUT_KEY_UP:
			glTranslatef(0., translate_factor, 0.);
			break;
		case GLUT_KEY_DOWN:
			glTranslatef(0., -1.*translate_factor, 0.);
			break;
		default:
			cout << "unused special: " << key << endl;
			break;
	}
	glutPostRedisplay();
}
/////////////////////////

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

void GlGlut::specialWrapper(int key, int mousex, int mousey) {
	instance->special(key, mousex, mousey);
}
/////////////////////////

GlGlut::GlGlut() {
	screen_width = DEF_SCREEN_W;
	screen_height = DEF_SCREEN_H;
	translate_factor = TRANSLATE_FACTOR;
	zoom_factor = ZOOM_FACTOR;
}

GlGlut::~GlGlut() {
	// Nothing to do here
}

void GlGlut::setInstance() {
	instance = this;
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
	glutSpecialFunc(specialWrapper);

	// Start
	reshape(screen_width, screen_height);
	glutIdleFunc(idleWrapper);
	glutMainLoop();
}
