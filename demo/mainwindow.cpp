#include "mainwindow.h"

#include <QPainter>
#include <QtGlobal>

using namespace voronoi;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	qsrand(1000); // static number to initialize rng
	
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
	painter.setPen(Qt::black);
	
	geometry::Rectangle boundingBox(0, 0, width(), height());
	
	for (std::map<VoronoiSite*, VoronoiCell*>::iterator it = diagram.cells().begin(); it != diagram.cells().end(); ++it) {
		std::pair<VoronoiSite*, VoronoiCell*> pair = *it;
		VoronoiCell* cell = pair.second;
		
		for (std::vector<VoronoiEdge*>::iterator edgesIt = cell->edges.begin(); edgesIt != cell->edges.end(); ++edgesIt) {
			geometry::Line line = (*edgesIt)->getRenderLine(boundingBox);
			
			painter.drawLine(line.startPoint().x(), line.startPoint().y(), line.endPoint().x(), line.endPoint().y());
		}
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
