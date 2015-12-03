#ifndef BIBLATEX_H
#define BIBLATEX_H

#include <QHash>
#include <QString>
#include <QStringList>

class BibLaTeX
{
public:
	static BibLaTeX& instance() { static BibLaTeX instance; return instance; }

	~BibLaTeX();


private:
	BibLaTeX();
	BibLaTeX(const BibLaTeX&);
	BibLaTeX& operator=(const BibLaTeX&);

	QHash <QString, QHash <QString, QStringList>> m_types;
	QHash <QString, QHash <QString, QString>> m_fields;
};

#endif // BIBLATEX_H
