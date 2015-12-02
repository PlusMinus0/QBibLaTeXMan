#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bibtableview.h"


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	BibTableView *t = this->findChild<BibTableView *>("tableView");
	t->setModel(new BibItemModel);
}

MainWindow::~MainWindow()
{
	delete ui;
}
