#ifndef TEST_H
#define TEST_H

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
};

#endif // TEST_H
