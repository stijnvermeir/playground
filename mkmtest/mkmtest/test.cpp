#include "test.h"

#include <mkm/mkm.h>
#include <mkm/parser.h>

#include <QDebug>

test::test(QObject *parent)
	: QObject(parent)
	, client_("https://sandbox.mkmapi.eu/ws/v1.1/output.json/", "CyWyAy36kiBIc2Xq", "UH4GA6J9QDHhQEIDQobwk6dQZk0PWjGm", "RpgaOf12KmK3reEcF0Y4AA6Zy0ZYOjQn", "IyTaypcimQITo7FoWvaqSUmZDC9nE7FF")
	, counter_(0)
{
	connect(&client_.networkAccessManager(), SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
}

test::~test()
{
}

void test::run()
{
	// sync
	// process(client_.findProduct("BlackCat", 1, 1, true));

	// async
	QNetworkReply* reply = client_.findProductAsync("BlackCat");
	reply->setProperty("dataRowIndex", 147852);

	reply = client_.findProductAsync("nivmizzetdracogenius");
	reply->setProperty("dataRowIndex", 987654);

	reply = client_.findProductAsync("anger");
	reply->setProperty("dataRowIndex", 888888);

	counter_ = 3;
}

void test::finished(QNetworkReply* reply)
{
	qDebug() << "ASYNC";
	qDebug() << "property dataRowIndex:" << reply->property("dataRowIndex").toInt();
	process(mkm::parseProducts(reply->readAll()));
	reply->deleteLater();
	--counter_;
	if (counter_ <= 0)
	{
		emit finished();
	}
}

void test::process(const QVector<mkm::Product>& result)
{
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
}
