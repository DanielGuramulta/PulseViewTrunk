#ifndef PULSEVIEWTRUNK_H
#define PULSEVIEWTRUNK_H

#include <QMainWindow>

namespace Ui
{
class PulseViewTrunk;
}

class PulseViewTrunk : public QMainWindow
{
	Q_OBJECT

public:
	explicit PulseViewTrunk(QWidget *parent = nullptr);
	~PulseViewTrunk();

private:
	Ui::PulseViewTrunk *ui;
};

#endif // PULSEVIEWTRUNK_H
