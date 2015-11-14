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

private:
	mkm::Mkm client_;
};

#endif // TEST_H
