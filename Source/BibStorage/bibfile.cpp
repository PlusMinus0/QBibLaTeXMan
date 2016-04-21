#include "bibfile.h"


#include <QFile>
#include <QTextStream>

#include <QDebug>

BibFile::BibFile(QString filePath)
{
	m_filePath = filePath;
}

BibLaTeXItemCollection BibFile::getDocuments() const
{
	BibLaTeXItemCollection documents;

	QFile bibFile(m_filePath);

	if (!bibFile.open(QIODevice::ReadOnly))
		return documents;

	QTextStream in(&bibFile);

	QString content = in.readAll();

	for (QString bibEntry : findEntries(content))
	{
		// TODO: These need to be processed at least string
		if (bibEntry == "preamble" || bibEntry == "string" || bibEntry == "comment" )
			continue;
		documents.append(parseEntry(bibEntry));
	}
	return documents;
}

BibLaTeXItem BibFile::parseEntry(const QString &entry) const
{
	QHash<QString, QString> bibEntry;

	QString head = entry.section(',', 0, 0).simplified().toLower();
	QString rest = entry.section(',', 1).simplified();

	// Head looks like @type{citationkey so take the part before the bracket, remove the @, then take the second part
	bibEntry["type"] = head.split('{')[0].simplified().remove(0,1);
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

		// If for some reason the property value is still embraced
		while (propertyValue.startsWith('{') && propertyValue.endsWith('}'))
		{
			propertyValue = propertyValue.remove(-1, 1);
			propertyValue = propertyValue.remove(0, 1);
		}

		index = rest.indexOf(',', index);
		rest = rest.remove(0, index+1);

		bibEntry[propertyType] = propertyValue;
	}


	return bibEntry;
}

QList<QString> BibFile::findEntries(const QString& content) const
{
	QList<QString> entries;

	QString rest = content.simplified();
	int indexStart = 0;
	int indexEnd = 0;
	int numBraces = 0;

	// Check if
	while ((indexStart = rest.indexOf('@', indexEnd)) > -1)
	{
		// Mark the beginning of an entry
		indexEnd = rest.indexOf('{', indexStart);
		numBraces = 1;		// Number of opening brackets found thus far

		// Try to find the closing brackets
		while (numBraces > 0)
		{
			// If an opening bracket exists and it comes before the next closing bracket, increase the bracket counter
			if ((rest.indexOf('{', indexEnd+1) != -1) && (rest.indexOf('{', indexEnd+1) < rest.indexOf('}', indexEnd+1)))
			{
				indexEnd = rest.indexOf('{', indexEnd+1);
				numBraces++;
			}
			else	// Else we found a closing bracket and we can reduce the counter of open brackets
			{
				indexEnd = rest.indexOf('}', indexEnd+1);
				numBraces--;
			}
		}

		entries.append(rest.mid(indexStart, indexEnd-indexStart));
	}

	return entries;

}

