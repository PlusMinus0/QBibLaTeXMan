#ifndef BIBITEMEDITWIDGET_H
#define BIBITEMEDITWIDGET_H

#include "bibitemmodel.h"

#include <QWidget>
#include <QStandardItemModel>

class BibItemEditWidget : public QWidget
{
	Q_OBJECT
public:
	explicit BibItemEditWidget(const QStandardItemModel &model, QWidget *parent = 0);
	~BibItemEditWidget();

private:
	const QStandardItemModel &m_model;

signals:

public slots:
};

#endif // BIBITEMEDITWIDGET_H
