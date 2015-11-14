#include "test.h"

#include <mkm/mkm.h>

#include <QDebug>

test::test(QObject *parent)
	: QObject(parent)
	, client_("https://sandbox.mkmapi.eu/ws/v1.1/output.json/", "CyWyAy36kiBIc2Xq", "UH4GA6J9QDHhQEIDQobwk6dQZk0PWjGm", "RpgaOf12KmK3reEcF0Y4AA6Zy0ZYOjQn", "IyTaypcimQITo7FoWvaqSUmZDC9nE7FF")
{
}

test::~test()
{
}

void test::run()
{
	QVector<mkm::Want> wants;

	mkm::Product p2 = client_.findProduct("acidicslime").first();
	mkm::Want w2;
	// w2.productId = p2.idProduct;
	w2.metaProductId = p2.idMetaproduct;
	w2.languageIds.push_back(1);
	w2.languageIds.push_back(2);
	w2.minCondition = mkm::Want::Poor;
	w2.buyPrice = 0.0;
	wants.push_back(w2);

	client_.addWants(239357, wants);

	emit finished();
}
