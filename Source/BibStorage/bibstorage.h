#ifndef BIBSTORAGE_H
#define BIBSTORAGE_H

#include "biblatexitemcollection.h"
#include "biblatexitem.h"

class BibStorage
{
public:
	BibStorage();
	virtual BibLaTeXItemCollection getDocuments() = 0;
};

#endif // BIBSTORAGE_H
