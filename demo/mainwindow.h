#pragma once

#include <voronoi.h>

#include <QMainWindow>
#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QList>
#include <QPoint>

class MainWindow
: public QMainWindow
{
	Q_OBJECT;

	public:
		MainWindow(QWidget* parent = 0);
	protected:
		voronoi::VoronoiDiagram diagram;
		QPixmap pixmap;
	
		void paintEvent(QPaintEvent* event);
		void resizeEvent(QResizeEvent* event);
		
		void createVoronoiDiagram();
		void recacheVoronoiDiagram();
		QList<QPoint> getSites();
		QSize sizeHint() const;
};
