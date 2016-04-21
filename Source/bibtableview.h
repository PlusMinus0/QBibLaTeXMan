#ifndef BIBTABLEVIEW_H
#define BIBTABLEVIEW_H

#include <QTableView>
#include <QHeaderView>
#include <QMouseEvent>
#include <QPoint>
#include <QMenu>
#include <QAction>

#include "bibitemmodel.h"

class BibTableView : public QTableView
{
	Q_OBJECT

public:
	BibTableView(QWidget * parent = 0);
	~BibTableView();

private:
	QMenu m_horizontalHeaderMenu;

private slots:
	void showHorizontalHeaderContextMenu(const QPoint &point);
	void showHideColum(QAction *action);


};

#endif // BIBTABLEVIEW_H
