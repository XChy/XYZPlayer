#include "PlaylistView.h"

PlaylistView::PlaylistView(QWidget* parent)
	:QTableView(parent)
	  ,mPopupMenu(new QMenu(this))
{
	verticalHeader()->setVisible(false);
	horizontalHeader()->setVisible(false);

	setSelectionBehavior(QAbstractItemView::SelectRows);
}
