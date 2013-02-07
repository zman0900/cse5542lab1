#include "GlGlut.h"

using namespace std;

GlGlut *GlGlut::instance = NULL;

void GlGlut::deviceCoordToViewPort(int *x, int *y) {
	// Adjust dev coords to square
	if (screen_width > screen_height) {
		*x -= (screen_width - screen_height) / 2;
		if (*x < 0 || *x > screen_height) {
			// Bad click
			*x = -1; *y = -1; return;
		}
	} else {
		*y -= (screen_height - screen_width) / 2;
		if (*y < 0 || *y > screen_width) {
			// Bad click
			*x = -1; *y = -1; return;
		}
	}
}

void GlGlut::deviceToWorldCoord(float *x, float *y) {
	int dim;
	if (screen_width > screen_height) {
		dim = screen_height;
	} else {
		dim = screen_width;
	}
	// Dev to screen (flip y)
	*y = dim - *y;
	// Make center point origin 0,0
	*x -= dim/2.;
	*y -= dim/2.;
	// Adjust to default world space (-1,1,-1,1)
	*x /= dim/2.;
	*y /= dim/2.;
	// Get projection matrix
	GLfloat params[16];
	glGetFloatv(GL_PROJECTION_MATRIX, params);
	// Adjust for translation
	*x -= params[12];
	*y -= params[13];
	// Adjust for zoom
	*x /= params[0];
	*y /= params[5];
}

void GlGlut::buildMenu() {
	glutCreateMenu(menuClickWrapper);
	glutAddMenuEntry("White", MENU_WHITE);
	glutAddMenuEntry("Red", MENU_RED);
	glutAddMenuEntry("Green", MENU_GREEN);
	glutAddMenuEntry("Blue", MENU_BLUE);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//// Glut callbacks /////
void GlGlut::display() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Display gray rectangle in middle
	glColor3f(.5, .5, .5);
	glRectf(-.5, -.5, .5, .5);
	glColor3f(colorr, colorg, colorb);

	// Display polylines
	for (list<Polyline>::iterator it = lines.begin(); it != lines.end(); ++it) {
		(*it).render();
	}

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
			glMatrixMode(GL_PROJECTION);
			glScalef(zoom_factor, zoom_factor, 1.);
			translate_factor *= 1./zoom_factor;
			glMatrixMode(GL_MODELVIEW);
			glutPostRedisplay();
			break;
		case 'z':
			glMatrixMode(GL_PROJECTION);
			glScalef(1./zoom_factor, 1./zoom_factor, 1.);
			translate_factor *= zoom_factor;
			glMatrixMode(GL_MODELVIEW);
			glutPostRedisplay();
			break;
		case 'q':
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			translate_factor = TRANSLATE_FACTOR;
			zoom_factor = ZOOM_FACTOR;
			glMatrixMode(GL_MODELVIEW);
			glutPostRedisplay();
			break;
		default:
			cout << "unused key: " << (int) key << endl;
			break;
	}
}

void GlGlut::menuClick(int value) {
	switch (value) {
		case MENU_WHITE:
			colorr = 1.;
			colorg = 1.;
			colorb = 1.;
			cout << "Color now white" << endl;
			break;
		case MENU_RED:
			colorr = 1.;
			colorg = 0.;
			colorb = 0.;
			cout << "Color now red" << endl;
			break;
		case MENU_GREEN:
			colorr = 0.;
			colorg = 1.;
			colorb = 0.;
			cout << "Color now green" << endl;
			break;
		case MENU_BLUE:
			colorr = 0.;
			colorg = 0.;
			colorb = 1.;
			cout << "Color now blue" << endl;
			break;
	}
	glColor3f(colorr, colorg, colorb);
	// Set color of current polyline
	if (lines.size() > 0) {
		lines.back().setColor(colorr, colorg, colorb);
	}
	glutPostRedisplay();
}

void GlGlut::mouseClick(int button, int state, int x, int y) {
	if (state == GLUT_UP) {
		cout << "click b:" << button << " x:" << x << " y:" << y << endl;
		deviceCoordToViewPort(&x, &y);
		if (x < 0 || y < 0) {
			cout << "click ignored" << endl;
		} else {
			float wx = x;
			float wy = y;
			deviceToWorldCoord(&wx, &wy);
			cout << "after: x:" << wx << " y:" << wy << endl;
			lines.push_back(Polyline(wx, wy, colorr, colorg, colorb));
			glutPostRedisplay();
		}
	}
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
			glMatrixMode(GL_PROJECTION);
			glTranslatef(-1.*translate_factor, 0., 0.);
			glMatrixMode(GL_MODELVIEW);
			break;
		case GLUT_KEY_RIGHT:
			glMatrixMode(GL_PROJECTION);
			glTranslatef(translate_factor, 0., 0.);
			glMatrixMode(GL_MODELVIEW);
			break;
		case GLUT_KEY_UP:
			glMatrixMode(GL_PROJECTION);
			glTranslatef(0., translate_factor, 0.);
			glMatrixMode(GL_MODELVIEW);
			break;
		case GLUT_KEY_DOWN:
			glMatrixMode(GL_PROJECTION);
			glTranslatef(0., -1.*translate_factor, 0.);
			glMatrixMode(GL_MODELVIEW);
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

void GlGlut::menuClickWrapper(int value) {
	instance->menuClick(value);
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
	colorr = 1.;
	colorg = 1.;
	colorb = 1.;
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

	// Setup
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Start
	buildMenu();
	reshape(screen_width, screen_height);
	glutIdleFunc(idleWrapper);
	glutMainLoop();
}
