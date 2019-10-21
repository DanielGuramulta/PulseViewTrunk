#include "pulseviewtrunk.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PulseViewTrunk w;
	w.show();

	return a.exec();
}
