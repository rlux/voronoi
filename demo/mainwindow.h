/**
  * (C) LGPL-3
  *
  * Voronoi++ <https://github.com/rlux/voronoi>
  *
  * Copyright: 2012 Lux, Scheibel
  * Authors:
  *     Roland Lux <rollux2000@googlemail.com>
  *     Willy Scheibel <willyscheibel@gmx.de>
  * 
  * This file is part of Voronoi++.
  *
  * Voronoi++ is free software: you can redistribute it and/or modify
  * it under the terms of the GNU Lesser General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  * 
  * Voronoi++ is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU Lesser General Public License for more details.
  * 
  * You should have received a copy of the GNU Lesser General Public License
  * along with Voronoi++.  If not, see <http://www.gnu.org/licenses/>.
  **/

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
		geometry::ConvexPolygon boundingBox;
		QPixmap pixmap;
		QPoint offset;
		QPoint lastMousePosition;
		bool dragging;
		int zoomLevel;
	
		float zoomFactor();
		
		void paintEvent(QPaintEvent* event);
		void mouseMoveEvent(QMouseEvent* event);
		void mousePressEvent(QMouseEvent* event);
		void mouseReleaseEvent(QMouseEvent* event);
		void wheelEvent(QWheelEvent* event);
		
		void createVoronoiDiagram();
		void recacheVoronoiDiagram();
		QList<QPoint> getSites();
		QSize sizeHint() const;
};
