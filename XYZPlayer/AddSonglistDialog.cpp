#include "AddSonglistDialog.h"
#include "ui_addsonglistdialog.h"

AddSonglistDialog::AddSonglistDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddSonglistDialog)
{
	ui->setupUi(this);
}

QString AddSonglistDialog::setSonglistName(const QString& name)
{
	ui->nameEdit->setText(name);
}

QString AddSonglistDialog::songlistName()
{
	return ui->nameEdit->text();
}

AddSonglistDialog::~AddSonglistDialog()
{
	delete ui;
}
