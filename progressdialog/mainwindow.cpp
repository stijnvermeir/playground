#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProgressDialog>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QThread>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(foo()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::longProcess()
{
	for (int i = 0; i < 50; ++i)
	{
		QThread::msleep(50);
		// uncomment to test exception
		if (i == 40) throw std::logic_error("Uh oh");
	}
}

void MainWindow::foo()
{
	QProgressDialog progress("Doing stuff ...", "", 0, 0, this);
	// disable input in other windows
	progress.setWindowModality(Qt::WindowModal);
	// disable cancel button
	progress.setCancelButton(nullptr);
	// disable close button
	progress.setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowTitleHint);


	QFutureWatcher<void> watcher;
	connect(&watcher, SIGNAL(finished()), &progress, SLOT(accept()));
	QFuture<std::exception_ptr> f = QtConcurrent::run([this]()
	{
		std::exception_ptr e;
		try
		{
			longProcess();
		}
		catch (...)
		{
			e = std::current_exception();
		}
		return e;
	});
	watcher.setFuture(f);

	// show progress bar (blocking)
	progress.exec();

	try
	{
		// handle exceptions if any
		auto e = f.result();
		if (e)
		{
			std::rethrow_exception(e);
		}
	}
	catch (const std::exception& e)
	{
		qDebug() << "Error: " << e.what();
	}

	qDebug() << "Done";
}
