#include "addsonglistdialog.h"
#include "ui_addsonglistdialog.h"

AddSonglistDialog::AddSonglistDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddSonglistDialog)
{
	ui->setupUi(this);
}

QString AddSonglistDialog::songlistName()
{
	return ui->nameEdit->text();
}

AddSonglistDialog::~AddSonglistDialog()
{
	delete ui;
}
