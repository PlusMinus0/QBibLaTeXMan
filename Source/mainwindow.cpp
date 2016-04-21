#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bibtableview.h"
#include "bibitemeditwidget.h"


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	BibItemModel *model = new BibItemModel();

	BibTableView *t = this->findChild<BibTableView *>("tableView");
	t->setModel(model);

	BibItemEditWidget *w = this->findChild<BibItemEditWidget *>("editWidget");
	w->setModel(model);


	connect(t, SIGNAL(clicked(QModelIndex)), w, SLOT(selectionChanged(QModelIndex)));
}

MainWindow::~MainWindow()
{
	delete ui;
}
