#include "test.h"

#include "mkm/mkm.h"

#include <QDebug>

test::test(QObject *parent)
	: QObject(parent)
{
}

test::~test()
{

}

void test::run()
{
	mkm::Mkm mkmClient{"CyWyAy36kiBIc2Xq", "UH4GA6J9QDHhQEIDQobwk6dQZk0PWjGm", "RpgaOf12KmK3reEcF0Y4AA6Zy0ZYOjQn", "IyTaypcimQITo7FoWvaqSUmZDC9nE7FF"};
	auto result = mkmClient.findProduct("Selesnyaevangel", 1, 1, true);
	for (const mkm::Product& product : result)
	{
		qDebug() << "idProduct:" << product.idProduct;
		qDebug() << "productName:" << product.names[1].productName;
		qDebug() << "expansion:" << product.expansion;
		qDebug() << "SELL:" << product.priceGuide.sell;
		qDebug() << "LOW:" << product.priceGuide.low;
		qDebug() << "LOWEX+:" << product.priceGuide.lowExPlus;
		qDebug() << "LOWFOIL:" << product.priceGuide.lowFoil;
		qDebug() << "AVG:" << product.priceGuide.avg;
		qDebug() << "TREND:" << product.priceGuide.trend;

		qDebug() << "";
	}

	emit finished();
}

