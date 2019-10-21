#include "pulseviewtrunk.h"
#include "ui_pulseviewtrunk.h"

PulseViewTrunk::PulseViewTrunk(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::PulseViewTrunk)
{
	ui->setupUi(this);
}

PulseViewTrunk::~PulseViewTrunk()
{
	delete ui;
}
