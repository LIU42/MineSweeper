#include "about.h"
#include "ui_about.h"

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent), ui(new Ui::AboutDialog)
{
	ui->setupUi(this);
	setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

AboutDialog::~AboutDialog()
{
	delete ui;
}
