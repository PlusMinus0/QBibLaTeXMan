#include "biblatex.h"


#include <QXmlStreamReader>
#include <QFile>
#include <QRegExp>

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
		QString name;

		while(xml.readNextStartElement())
		{
			type = xml.name().toString();

			if (type == "EntryTypes")
			{
				while (xml.readNextStartElement()) // EntryTypes
				{
					name = xml.attributes().value("Name").toString();

					QRegExp regex("[,\\s]+");	// Regex matches "," or whitespaces

					m_types[name]["RequiredFields"] = xml.attributes().value("RequiredFields").toString().split(regex);

					m_types[name]["OptionalFields"] = xml.attributes().value("OptionalFields").toString().split(regex);
					xml.skipCurrentElement();

				}
			}
			else if (type == "EntryFields")
			{
				while (xml.readNextStartElement()) // EntryField
				{
					name = xml.attributes().value("Name").toString();
					m_fieldsOrdered.append(name);

					m_fields[name]["Type"] = xml.attributes().value("Type").toString();
					m_fields[name]["Tooltip"] = xml.readElementText();
				}
			}
		}

		if (xml.hasError())
			qDebug() << xml.errorString();

		settingsFile->close();
	}


}

BibLaTeX::~BibLaTeX()
{

}

