#include "bibitemeditwidget.h"

BibItemEditWidget::BibItemEditWidget(const QStandardItemModel &model, QWidget *parent) : QWidget(parent)
{
	m_model = model;
}

BibItemEditWidget::~BibItemEditWidget()
{

}

