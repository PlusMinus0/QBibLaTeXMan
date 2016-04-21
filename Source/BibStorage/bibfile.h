#ifndef BIBFILE_H
#define BIBFILE_H

#include "bibstorage.h"

#include <QHash>
#include <QString>

class BibFile : public BibStorage
{
public:
	BibFile(QString filePath);
	BibLaTeXItemCollection getDocuments() const;

private:
	QHash<QString, QString> parseEntry(const QString &entry) const;
	QList<QString> findEntries(const QString &content) const;
	QString m_filePath;
};

#endif // BIBFILE_H
