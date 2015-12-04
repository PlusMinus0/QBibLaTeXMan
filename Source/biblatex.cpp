#include "biblatex.h"


#include <QXmlStreamReader>
#include <QFile>

#include <QDebug>

QMap<QString, QHash <QString, QStringList>> BibLaTeX::m_types;
QMap <QString, QHash <QString, QString>> BibLaTeX::m_fields;
QStringList BibLaTeX::m_fieldsOrdered = { "type", "citationkey" };

BibLaTeX::BibLaTeX()
{
	QFile *settingsFile = new QFile("/home/mbrandt/Projects/QBibLaTeXMan/biblatex.conf.xml");
	if (settingsFile->open(QIODevice::ReadOnly | QIODevice::Text))
	{

		QXmlStreamReader xml(settingsFile);

		if (!(xml.readNextStartElement() && xml.name() == "BibLaTeX"))
		{
			return;
		}

		QString type;
		QString attribute;
		QString value;
		QString name;

		while(xml.readNextStartElement())
		{
			type = xml.name().toString();

			if (type == "EntryTypes")
			{
				while (xml.readNextStartElement()) // EntryTypes
				{
					name = xml.attributes().value("Name").toString();

					while (xml.readNextStartElement()) // Attributes
					{
						attribute = xml.name().toString();

						while (xml.readNextStartElement())
						{
							m_types[name][attribute].append(xml.readElementText());
						}
					}
				}
			}
			else if (type == "EntryFields")
			{
				while (xml.readNextStartElement()) // EntryField
				{
					name = xml.attributes().value("Name").toString();
					m_fieldsOrdered.append(name);
					while (xml.readNextStartElement()) // Attributes of EntryField
					{
						attribute = xml.name().toString();
						value = xml.readElementText();

						m_fields[name][attribute] = value;
					}
				}
			}
		}

		if (xml.hasError())
			qDebug() << xml.errorString();

		settingsFile->close();
	}

	qDebug() << m_types;
	qDebug() << m_fields;

}

BibLaTeX::~BibLaTeX()
{

}

