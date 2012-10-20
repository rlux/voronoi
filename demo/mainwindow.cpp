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
#include <cmath>

using namespace voronoi;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), dragging(false), zoomLevel(0)
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
	
	recacheVoronoiDiagram();
}

void MainWindow::recacheVoronoiDiagram()
{
	geometry::Rectangle boundingRect = boundingBox.boundingBox();
	float zf = zoomFactor();
	
	pixmap = QPixmap(boundingRect.width() * zf, boundingRect.height() * zf + 1);
	pixmap.fill(Qt::white);
	
	QPainter painter(&pixmap);
	//painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::black);
	
	for (std::map<VoronoiSite*, VoronoiCell*>::iterator it = diagram.cells().begin(); it != diagram.cells().end(); ++it) {
		std::pair<VoronoiSite*, VoronoiCell*> pair = *it;
		VoronoiCell* cell = pair.second;
		
		for (std::vector<VoronoiEdge*>::iterator edgesIt = cell->edges.begin(); edgesIt != cell->edges.end(); ++edgesIt) {
			geometry::Line line = (*edgesIt)->getRenderLine(boundingBox);
			
			painter.drawLine(
				line.startPoint().x() * zf,
				line.startPoint().y() * zf,
				line.endPoint().x() * zf,
				line.endPoint().y() * zf
			);
		}
	}
	
	painter.setPen(Qt::red);
	
	for (std::vector<geometry::Line>::const_iterator it = boundingBox.edges().begin(); it != boundingBox.edges().end(); ++it) {
		const geometry::Line& line = *it;
		
		painter.drawLine(
			line.startPoint().x() * zf,
			line.startPoint().y() * zf,
			line.endPoint().x() * zf,
			line.endPoint().y() * zf
		);
	}
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	
	painter.fillRect(0, 0, width(), height(), Qt::white);
	painter.drawPixmap(offset.x(), offset.y(), pixmap);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
	if (dragging) {
		offset += event->pos()-lastMousePosition;
		lastMousePosition = event->pos();
		update();
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
	float oldZoomFactor = zoomFactor();
	
	if (event->delta() > 0) {
		if (zoomLevel >= 10) {
			return;
		}
		
		zoomLevel++;
		
		
	} else {
		if (zoomLevel <= -10) {
			return;
		}
		
		zoomLevel--;
	}
	
	offset = (offset - event->pos()) / oldZoomFactor * zoomFactor() + event->pos();
	
	recacheVoronoiDiagram();
	update();
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
	return pow(1.3, zoomLevel);
}
