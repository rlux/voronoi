#include <QApplication>

#include "mainwindow.h"

#include <voronoi.h>
#include <iostream>

using namespace geometry;

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	
	MainWindow w;
	
	w.show();
	
	return app.exec();
}
