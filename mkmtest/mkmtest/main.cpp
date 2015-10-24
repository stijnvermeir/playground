#include <QCoreApplication>
#include <QTimer>

#include "test.h"

int main(int argc, char** argv)
{
	QCoreApplication a(argc, argv);

	test* t = new test(&a);

	QObject::connect(t, SIGNAL(finished()), &a, SLOT(quit()));

	QTimer::singleShot(0, t, SLOT(run()));

	return a.exec();
}
