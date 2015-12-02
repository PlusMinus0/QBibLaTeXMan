#ifndef BIBFILE_H
#define BIBFILE_H

#include "bibstorage.h"

#include <QHash>
#include <QString>

class BibFile : public BibStorage
{
public:
	BibFile(QString filePath);
	QList<QHash<QString, QString> > getDocuments();

private:
	QHash<QString, QString> parseEntry(QString entry);
	QList<QString> findEntries(const QString &content);
	QString m_filePath;
};

#endif // BIBFILE_H
