#include "bibtableview.h"

#include <QAction>

BibTableView::BibTableView(QWidget *parent) : QTableView(parent)
{
	this->verticalHeader()->hide();
	this->setSelectionBehavior(QAbstractItemView::SelectRows);

	QHeaderView *header = this->horizontalHeader();

	header->setDragEnabled(true);
	header->setDragDropMode(QAbstractItemView::InternalMove);
	header->setSectionsMovable(true);
	header->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(header, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showHorizontalHeaderContextMenu(const QPoint &)));
	connect(&m_horizontalHeaderMenu, SIGNAL(triggered(QAction*)), this, SLOT(showHideColum(QAction*)));
}

BibTableView::~BibTableView()
{

}

void BibTableView::showHorizontalHeaderContextMenu(const QPoint &point)
{
	m_horizontalHeaderMenu.close();

	m_horizontalHeaderMenu.clear();

	for (int i = 0; i < this->horizontalHeader()->count(); i++)
	{
		QAction *action = new QAction(this->model()->headerData(i, Qt::Horizontal).toString(), &m_horizontalHeaderMenu);
		action->setCheckable(true);
		action->setData(i);

		if (this->horizontalHeader()->isSectionHidden(i))
			action->setChecked(false);
		else
			action->setChecked(true);

		m_horizontalHeaderMenu.addAction(action);
	}
	m_horizontalHeaderMenu.exec(QCursor::pos());
	Q_UNUSED(point);
}

void BibTableView::showHideColum(QAction *action)
{
	this->horizontalHeader()->setSectionHidden(action->data().toInt(), !action->isChecked());
}
