#pragma once

#include <voronoi.h>

#include <QMainWindow>
#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
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
		QPoint offset;
		QPoint lastMousePosition;
		bool dragging;
		int zoomLevel;
	
		float zoomFactor();
		
		void paintEvent(QPaintEvent* event);
		void resizeEvent(QResizeEvent* event);
		void mouseMoveEvent(QMouseEvent* event);
		void mousePressEvent(QMouseEvent* event);
		void mouseReleaseEvent(QMouseEvent* event);
		void wheelEvent(QWheelEvent* event);
		
		void createVoronoiDiagram();
		void recacheVoronoiDiagram();
		QList<QPoint> getSites();
		QSize sizeHint() const;
};
