#include "mainwindow.h"

#include <QPainter>
#include <QtGlobal>
#include <cmath>

using namespace voronoi;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), dragging(false), zoomLevel(0)
{
	qsrand(1000); // static number to initialize rng
	
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
	pixmap = QPixmap(width(), height());
	pixmap.fill(Qt::white);
	
	QPainter painter(&pixmap);
	//painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::black);
	
	geometry::ConvexPolygon boundingBox;
	boundingBox << geometry::Point(1280 / 3, 0) << geometry::Point(2 * 1280 / 3, 0) << geometry::Point(1280, 720 / 2) << geometry::Point(2 * 1280 / 3, 720) << geometry::Point(1280 / 3, 720) << geometry::Point(0, 2 * 720 / 3) << geometry::Point(0, 720 / 3);
	float zf = zoomFactor();
	
	for (std::map<VoronoiSite*, VoronoiCell*>::iterator it = diagram.cells().begin(); it != diagram.cells().end(); ++it) {
		std::pair<VoronoiSite*, VoronoiCell*> pair = *it;
		VoronoiCell* cell = pair.second;
		
		for (std::vector<VoronoiEdge*>::iterator edgesIt = cell->edges.begin(); edgesIt != cell->edges.end(); ++edgesIt) {
			geometry::Line line = (*edgesIt)->getRenderLine(boundingBox);
			
			painter.drawLine(
				offset.x()+line.startPoint().x() * zf,
				offset.y()+line.startPoint().y() * zf,
				offset.x()+line.endPoint().x() * zf,
				offset.y()+line.endPoint().y() * zf
			);
		}
	}
	
	painter.setPen(Qt::red);
	
	for (std::vector<geometry::Line>::const_iterator it = boundingBox.edges().begin(); it != boundingBox.edges().end(); ++it) {
		const geometry::Line& line = *it;
		
		painter.drawLine(
			offset.x()+line.startPoint().x() * zf,
			offset.y()+line.startPoint().y() * zf,
			offset.x()+line.endPoint().x() * zf,
			offset.y()+line.endPoint().y() * zf
		);
	}
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	
	painter.drawPixmap(0, 0, pixmap);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	recacheVoronoiDiagram();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
	if (dragging) {
		offset += event->pos()-lastMousePosition;
		lastMousePosition = event->pos();
		recacheVoronoiDiagram();
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
