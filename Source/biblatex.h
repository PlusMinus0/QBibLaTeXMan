#ifndef BIBLATEX_H
#define BIBLATEX_H

#include <QMap>
#include <QHash>
#include <QString>
#include <QStringList>


class BibLaTeX
{
public:
	static BibLaTeX& instance() { static BibLaTeX instance; return instance; }

	QStringList types() { return m_types.keys(); }
	QStringList fields() { return m_fields.keys(); }
	QStringList fieldsOrdered() { return m_fieldsOrdered; }
	QHash<QString, QString> fieldProperties(const QString& field) { return m_fields[field]; }
	QStringList requiredFields(const QString& type) { return m_types[type]["RequiredFields"]; }
	QStringList optionalFields(const QString& type) { return m_types[type]["OptionalFields"]; }

	~BibLaTeX();


private:
	BibLaTeX();
	BibLaTeX(const BibLaTeX&);
	BibLaTeX& operator=(const BibLaTeX&);

	static QMap <QString, QHash <QString, QStringList>> m_types;	// Use QMap to ensure the keys are always sorted
	static QMap <QString, QHash <QString, QString>> m_fields;		// Use QMap to ensure the keys are always sorted
	static QStringList m_fieldsOrdered;
};

#endif // BIBLATEX_H

