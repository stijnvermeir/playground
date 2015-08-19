#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProgressDialog>
#include <QThread>
#include <QDebug>

#include <future>
#include <iostream>

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
		// if (i == 40) throw std::logic_error("Uh oh");
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

	// start asynchronous task
	auto f = std::async([&progress, this]()
	{
		try
		{
			longProcess();
			qDebug() << "Long event finished";
			progress.done(0);
			qDebug() << "Progress bar done";
		}
		catch (...)
		{
			progress.done(1);
			qDebug() << "Progress bar done because of error";
			// rethrow after progress bar closed
			throw;
		}
	});

	// show progress bar (blocking)
	progress.exec();

	try
	{
		// handle exceptions if any
		f.get();
	}
	catch (const std::exception& e)
	{
		qDebug() << "Error: " << e.what();
	}

	qDebug() << "Done";
}
