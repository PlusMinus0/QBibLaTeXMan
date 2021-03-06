#include "bibitemmodel.h"
#include "BibStorage/bibfile.h"
#include "biblatex.h"

#include <QDebug>

BibItemModel::BibItemModel(QObject *parent) :
	QStandardItemModel(parent)
{
	//loadItems();

	BibLaTeX::instance();
}

QVariant BibItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal)
	{
		return BibLaTeX::instance().fieldsOrdered().at(section);
	}
	return QVariant();

}

void BibItemModel::loadItems(const BibStorage &storage)
{
	auto items = storage.getDocuments();

	int row = 0;
	int column = 0;

	for (auto i : items)
	{
		column = 0;
		for (QString property : BibLaTeX::instance().fieldsOrdered())
		{
			QStandardItem *item = new QStandardItem(i[property]);
			this->setItem(row, column, item);
			column++;
		}
		row++;
	}
}



QStringList BibItemModel::BIB_PROPERTIES = QStringList({
														   "type",
														   "citationkey",
														   "author",
														   "abstract",
														   "doi"
});
