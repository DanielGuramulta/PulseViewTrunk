#include "pulseviewtrunk.h"
#include <QApplication>
#include <pv/mainwindow.hpp>
#include <pv/devicemanager.hpp>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	auto context = sigrok::Context::create();

	pv::DeviceManager d(context, "", false);
	pv::MainWindow m(d);

	m.show();

	return a.exec();
}
