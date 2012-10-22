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
#include <QPainterPath>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QList>
#include <QPoint>
#include <QPropertyAnimation>
#include <QVariant>

class MainWindow
: public QMainWindow
{
	Q_OBJECT;
	
	Q_PROPERTY(float zoomLevel READ zoomLevel WRITE setZoomLevel);

	public:
		MainWindow(QWidget* parent = 0);
	protected:
		voronoi::VoronoiDiagram diagram;
		geometry::ConvexPolygon boundingBox;
		QPainterPath voronoiPath;
		QPainterPath halfEdgesDebugPath; //remove later
		QPainterPath sitesPath;
		QPainterPath boundingPath;
		QPoint lastMousePosition;
		bool dragging;
		QPoint _offset;
		float _zoomLevel;
		QPropertyAnimation zoomAnimation;
		
		float zoomFactor();
		float zoomFactor(float level);
		float zoomLevel();
		QPoint offset();
		
		void paintEvent(QPaintEvent* event);
		void mouseMoveEvent(QMouseEvent* event);
		void mousePressEvent(QMouseEvent* event);
		void mouseReleaseEvent(QMouseEvent* event);
		void wheelEvent(QWheelEvent* event);
		
		void createVoronoiDiagram();
		void prepareRenderingObjects();
		QList<QPoint> getSites();
		QSize sizeHint() const;
	protected slots:
		void setZoomLevel(float level);
		void setZoomLevel(const QVariant& level);
		void setOffset(const QPoint& point);
};
