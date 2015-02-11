#include <QApplication>
#include <QPolygon>

int main(int argc, char** argv)
{
	QPolygon p;
	p << QPoint(0, 0) << QPoint(100, 0) << QPoint(100, 100) << QPoint(0, 100) << QPoint(0, 0);
	QRect rect = p.boundingRect();

	return 1;
}
