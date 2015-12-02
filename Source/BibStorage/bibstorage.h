#ifndef BIBSTORAGE_H
#define BIBSTORAGE_H

#include <QHash>
#include <QString>

class BibStorage
{
public:
	BibStorage();
	virtual QList<QHash<QString, QString> > getDocuments() = 0;
};

#endif // BIBSTORAGE_H
