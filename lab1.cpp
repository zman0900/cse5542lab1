#include <iostream>

#include "GlGlut.h"

using namespace std;

int main(int argc, char *argv[]) {
	cout << "CSE 5542 - Lab 1" << endl;
	cout << "Dan Ziemba, 2013" << endl << endl;
	cout << "Controls:" << endl;
	cout << "\tarrows - Pan" << endl;
	cout << "\tclick - start new ployline at mouse" << endl;
	cout << "\t'a' - zoom in" << endl;
	cout << "\t'z' - zoom out" << endl;
	cout << "\t'q' - reset pan and zoom" << endl;
	cout << "\t'f' - add vertex to current polyline" << endl;
	cout << "\t't' - rotate last vertex by 10 degrees" << endl;
	cout << "\t'S' - enlarge last vertex by 50%" << endl;
	cout << "\t's' - shrink last vertex by 50%" << endl;
	cout << "\t'p' - draw polygon" << endl;
	cout << "\t'n' - draw star" << endl;
	cout << "\t'r' - draw spiral" << endl;
	cout << "\t'c' - remove all polylines" << endl;

	GlGlut g;
	g.start(&argc, argv);

	return 0;
}
