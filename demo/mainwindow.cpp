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

#include "mainwindow.h"

#include <QPainter>
#include <QtGlobal>
#include <QPropertyAnimation>
#include <qmath.h>

using namespace voronoi;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), dragging(false), _zoomLevel(0), zoomAnimation(this, "zoomLevel")
{
	qsrand(1000); // static number to initialize rng
	
	boundingBox
		<< geometry::Point(1280 / 3, 0)
		<< geometry::Point(2 * 1280 / 3, 0)
		<< geometry::Point(1280, 720 / 2)
		<< geometry::Point(2 * 1280 / 3, 720)
		<< geometry::Point(1280 / 3, 720)
		<< geometry::Point(0, 2 * 720 / 3)
		<< geometry::Point(0, 720 / 3);
	
	setMouseTracking(true);
	createVoronoiDiagram();
	prepareRenderingObjects();
	
	zoomAnimation.setDuration(300);
}

void MainWindow::createVoronoiDiagram()
{
	QList<QPoint> qtSites = getSites();
	std::vector<VoronoiSite*> sites;
	
	for (QList<QPoint>::iterator it = qtSites.begin(); it != qtSites.end(); ++it) {
		QPoint p = *it;
		
		sites.push_back(new VoronoiSite(p.x(), p.y()));
	}
	
	VoronoiDiagram::removeDuplicates(sites);
	
	diagram.initialize(sites);
	
	diagram.calculate();
}

void MainWindow::prepareRenderingObjects()
{
	geometry::Rectangle boundingRect = boundingBox.boundingBox();
	
	voronoiPath = QPainterPath();
	boundingPath = QPainterPath();
	
	for (std::map<VoronoiSite*, VoronoiCell*>::iterator it = diagram.cells().begin(); it != diagram.cells().end(); ++it) {
		std::pair<VoronoiSite*, VoronoiCell*> pair = *it;
		VoronoiSite* site = pair.first;
		VoronoiCell* cell = pair.second;
		
		
		for (std::vector<VoronoiEdge*>::iterator edgesIt = cell->edges.begin(); edgesIt != cell->edges.end(); ++edgesIt) {
			geometry::Line line = (*edgesIt)->getRenderLine(boundingBox);
			
			voronoiPath.moveTo(line.startPoint().x(), line.startPoint().y());
			voronoiPath.lineTo(line.endPoint().x(), line.endPoint().y());
		}
		
		geometry::Point position = site->position();
		if (boundingBox.contains(position)) {
			sitesPath.addEllipse(QPointF(position.x(), position.y()), 1, 1);
		}
		
		//halfEdgesDebugPath
		
		/*VoronoiHalfEdge* begin = cell->edges[0]->halfEdgeFor(site)->begin();
		geometry::Point p = begin->startPoint();
		halfEdgesDebugPath.moveTo(p.x(), p.y());
		VoronoiHalfEdge* he = begin;
		while (he->next()) {
			he = he->next();
			p = he->startPoint();
			halfEdgesDebugPath.lineTo(p.x(), p.y());
			if (he==begin) break;
		}*/
		
		// halfEdgesDebugPath end
	}
	
	for (std::vector<geometry::Line>::const_iterator it = boundingBox.edges().begin(); it != boundingBox.edges().end(); ++it) {
		const geometry::Line& line = *it;
		
		boundingPath.moveTo(line.startPoint().x(), line.startPoint().y());
		boundingPath.lineTo(line.endPoint().x(), line.endPoint().y());
	}
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	
	double zf = zoomFactor();
	
	painter.translate(offset());
	painter.scale(zf, zf);
	
	painter.setPen(Qt::gray);
	painter.setBrush(Qt::gray);
	painter.drawPath(sitesPath);	
	painter.setBrush(Qt::transparent);
	
	painter.setPen(Qt::black);
	painter.drawPath(voronoiPath);
	
	painter.setPen(Qt::red);
	painter.drawPath(boundingPath);
	
	painter.setPen(Qt::red);
	painter.drawPath(halfEdgesDebugPath);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
	if (dragging) {
		setOffset(offset() + event->pos()-lastMousePosition);
		lastMousePosition = event->pos();
		repaint();
	}
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button()==Qt::LeftButton) {
		lastMousePosition = event->pos();
		dragging = true;
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button()==Qt::LeftButton) {
		dragging = false;
	}
}

void MainWindow::wheelEvent(QWheelEvent* event)
{
	float oldZoomLevel = zoomLevel();
	if (zoomAnimation.state() == QAbstractAnimation::Running && !zoomAnimation.endValue().isNull()) {
		oldZoomLevel = zoomAnimation.endValue().toFloat();
	}
	
	float newZoomLevel = 0.f;
	
	if (event->delta() > 0) {
		if (oldZoomLevel >= 10) {
			return;
		}
		
		newZoomLevel = qMin(10.f, oldZoomLevel+1);
	} else {
		if (oldZoomLevel <= -10) {
			return;
		}
		
		newZoomLevel = qMax(-10.f, oldZoomLevel-1);
	}
	
	if (zoomAnimation.state() == QAbstractAnimation::Running) {
		zoomAnimation.stop();
		zoomAnimation.setStartValue(zoomAnimation.currentValue());
	} else {
		zoomAnimation.setStartValue(oldZoomLevel);
		
		lastMousePosition = event->pos();
	}
	
	zoomAnimation.setEndValue(newZoomLevel);
	zoomAnimation.start();
}

QList<QPoint> MainWindow::getSites()
{
	QList<QPoint> sites;
	
	for (unsigned i=0; i < 1000; ++i) {
		sites << QPoint(qrand() % 1280, qrand() % 720);
	}
	
	return sites;
}

QSize MainWindow::sizeHint() const
{
	return QSize(1280, 720);
}

float MainWindow::zoomFactor()
{
	return zoomFactor(zoomLevel());
}

float MainWindow::zoomFactor(float level)
{
	return qPow(1.3, level);
}

float MainWindow::zoomLevel()
{
	return _zoomLevel;
}

void MainWindow::setZoomLevel(float level)
{
	_offset = (offset() - lastMousePosition) / zoomFactor(_zoomLevel) * zoomFactor(level) + lastMousePosition;
	
	_zoomLevel = level;
	
	repaint();
}

void MainWindow::setZoomLevel(const QVariant& level)
{
	setZoomLevel(level.toFloat());
}

QPoint MainWindow::offset()
{
	return _offset;
}

void MainWindow::setOffset(const QPoint& point)
{
	_offset = point;
}
