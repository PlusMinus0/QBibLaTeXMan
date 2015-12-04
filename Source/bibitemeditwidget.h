#ifndef BIBITEMEDITWIDGET_H
#define BIBITEMEDITWIDGET_H

#include "bibitemmodel.h"

#include <QWidget>
#include <QAbstractItemModel>
#include <QDataWidgetMapper>
#include <QFormLayout>

class BibItemEditWidget : public QWidget
{
	Q_OBJECT
public:
	explicit BibItemEditWidget(QWidget *parent = 0);
	~BibItemEditWidget();

	void setModel(QAbstractItemModel *model);

private:
	QDataWidgetMapper m_mapper;
	QFormLayout *m_layout;

signals:

public slots:
	void selectionChanged(const QModelIndex &index);
};

#endif // BIBITEMEDITWIDGET_H
