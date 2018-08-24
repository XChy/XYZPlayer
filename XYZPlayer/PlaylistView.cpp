#include "PlaylistView.h"

PlaylistView::PlaylistView(QWidget* parent)
	:QTableView(parent)
	  ,mPopupMenu(new QMenu(this))
{

}
