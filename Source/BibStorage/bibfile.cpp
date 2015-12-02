#include "bibfile.h"


#include <QFile>
#include <QTextStream>

BibFile::BibFile(QString filePath)
{
	m_filePath = filePath;
}

QList<QHash<QString, QString> > BibFile::getDocuments()
{
	QList<QHash<QString, QString> > documents;

	QFile bibFile(m_filePath);

	if (!bibFile.open(QIODevice::ReadOnly))
		return documents;

	QTextStream in(&bibFile);

	QString content = in.readAll();

	for (QString bibEntry : findEntries(content))
	{
		if (bibEntry == "preamble" || bibEntry == "string" || bibEntry == "comment" )
			continue;
		documents.append(parseEntry(bibEntry));
	}
	return documents;
}

QHash<QString, QString> BibFile::parseEntry(QString entry)
{
	QHash<QString, QString> bibEntry;

	QString head = entry.section(',', 0, 0).simplified().toLower();
	QString rest = entry.section(',', 1).simplified();

	bibEntry["type"] = head.split('{')[0].simplified();
	bibEntry["citationkey"] = head.split('{')[1].simplified();

	QString propertyType;
	QString propertyValue;

	int index = 0;
	int startIndex = 0;
	int numBraces = 0;

	while (rest.indexOf('=') != -1)
	{
		startIndex = 0;
		index = 0;
		// Get name of property
		propertyType = rest.section('=', 0, 0).simplified().toLower();

		// And take the rest
		rest = rest.section('=', 1).simplified();

		// Find property values
		if (rest.startsWith('"'))
		{
			startIndex = 1;
			index = rest.indexOf('"', 1);
		}
		else if (rest.startsWith('{'))
		{
			startIndex = 1;
			numBraces = 1;

			while (numBraces > 0)
			{
				if ((rest.indexOf('{', index+1) < rest.indexOf('}', index+1)) && rest.indexOf('{', index+1) != -1)
				{
					index = rest.indexOf('{', index+1);
					numBraces++;
				}
				else
				{
					index = rest.indexOf('}', index+1);
					numBraces--;
				}
			}
		}
		else
		{
			startIndex = 0;
			index = rest.indexOf(',', startIndex)+1;
		}

		propertyValue = rest.mid(startIndex, index-1);
		index = rest.indexOf(',', index);
		rest = rest.remove(0, index+1);

		bibEntry[propertyType] = propertyValue;
	}


	return bibEntry;
}

QList<QString> BibFile::findEntries(const QString& content)
{
	QList<QString> entries;

	QString rest = content.simplified();
	int index = 0;
	int numBraces = 0;

	while (rest.startsWith('@'))
	{
		index = rest.indexOf('{');
		numBraces = 1;

		while (numBraces > 0)
		{
			if ((rest.indexOf('{', index+1) < rest.indexOf('}', index+1)) && rest.indexOf('{', index+1) != -1)
			{
				index = rest.indexOf('{', index+1);
				numBraces++;
			}
			else
			{
				index = rest.indexOf('}', index+1);
				numBraces--;
			}
		}

		entries.append(rest.mid(1, index));
		rest = rest.remove(0, index+1).simplified();
	}

	return entries;

}

