#ifndef TEST_H
#define TEST_H

#include <mkm/mkm.h>

#include <QObject>

class test : public QObject
{
	Q_OBJECT
public:
	explicit test(QObject *parent = 0);
	~test();

signals:
	void finished();

public slots:
	void run();

private slots:
	void finished(QNetworkReply* reply);

private:
	void process(const QVector<mkm::Product>& result);

	mkm::Mkm client_;
	int counter_;
};

#endif // TEST_H
