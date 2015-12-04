#include "bibitemeditwidget.h"

#include <QComboBox>

#include <QDebug>
BibItemEditWidget::BibItemEditWidget(QWidget *parent) : QWidget(parent)
{
	m_layout = new QFormLayout();

	m_layout->addRow("Type", new QComboBox());

	this->setLayout(m_layout);
}

BibItemEditWidget::~BibItemEditWidget()
{

}

void BibItemEditWidget::setModel(QAbstractItemModel *model)
{
	m_mapper.setModel(model);

}

void BibItemEditWidget::selectionChanged(const QModelIndex &index)
{
	if (index.isValid())
		m_mapper.setCurrentModelIndex(index);
	qDebug() << index;
}

