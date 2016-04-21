#ifndef BIBITEMEDITWIDGET_H
#define BIBITEMEDITWIDGET_H

#include "bibitemmodel.h"

#include <QWidget>
#include <QAbstractItemModel>
#include <QDataWidgetMapper>
#include <QFormLayout>
#include <QComboBox>
#include <QList>

class BibItemEditWidget : public QWidget
{
	Q_OBJECT
public:
	explicit BibItemEditWidget(QWidget *parent = 0);
	~BibItemEditWidget();

	void setModel(QAbstractItemModel *model);

private:
	void initComboBox();
	void clearLayout();

	QDataWidgetMapper m_mapper;
	QFormLayout *m_layout;
	QComboBox *m_typeComboBox = NULL;

	QList<QWidget*> m_fields;



signals:

public slots:
	void selectionChanged(const QModelIndex &index);

private slots:
	void rebuild(const QString &type);
};

#endif // BIBITEMEDITWIDGET_H
