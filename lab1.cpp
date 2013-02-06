#include <iostream>

#include "GlGlut.h"

using namespace std;

int main(int argc, char *argv[]) {
	cout << "CSE 5542 - Lab 1" << endl;
	cout << "Dan Ziemba, 2013" << endl << endl;
	cout << "Controls:" << endl;
	cout << "\tarrows - Pan" << endl;
	cout << "\t'a' - zoom in" << endl;
	cout << "\t'z' - zoom out" << endl;
	cout << "\t'q' - reset pan and zoom" << endl;

	GlGlut g;
	g.start(&argc, argv);

	return 0;
}
