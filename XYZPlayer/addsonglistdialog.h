#ifndef ADDSONGLISTDIALOG_H
#define ADDSONGLISTDIALOG_H

#include <QDialog>

namespace Ui {
class AddSonglistDialog;
}

class AddSonglistDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit AddSonglistDialog(QWidget *parent = nullptr);
		QString songlistName();
		~AddSonglistDialog();

	private:
		Ui::AddSonglistDialog *ui;
};

#endif // ADDSONGLISTDIALOG_H
