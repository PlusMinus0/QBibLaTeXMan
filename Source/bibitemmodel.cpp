#include "bibitemmodel.h"
#include "BibStorage/bibstorage.h"
#include "BibStorage/bibfile.h"

BibItemModel::BibItemModel(QObject *parent) :
	QStandardItemModel(parent)
{
	loadItems();
}

QVariant BibItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal)
	{
		return BIB_PROPERTIES.at(section);
	}
	return QVariant();

}

void BibItemModel::loadItems()
{
	BibFile bibfile("proxiVision.bib");
	auto items = bibfile.getDocuments();

	int row = 0;
	int column = 0;

	for (auto i : items)
	{
		column = 0;
		for (QString property : BIB_PROPERTIES)
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
