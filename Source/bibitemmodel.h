#ifndef BIBITEMMODEL_H
#define BIBITEMMODEL_H

#include "BibStorage/bibstorage.h"

#include <QStandardItemModel>
#include <QStringList>
#include <QString>

class BibItemModel : public QStandardItemModel
{
	Q_OBJECT
public:
	static QStringList BIB_PROPERTIES;

	explicit BibItemModel(QObject *parent = 0);

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

signals:

public slots:
	void loadItems(const BibStorage& storage);

};

#endif // BIBITEMMODEL_H
