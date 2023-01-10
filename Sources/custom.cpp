#include "custom.h"
#include "ui_custom.h"

CustomDialog::CustomDialog(QWidget* parent) : QDialog(parent), ui(new Ui::CustomDialog)
{
	ui->setupUi(this);
	connect(ui->doneButton, &QPushButton::clicked, this, &CustomDialog::inputDone);
}

CustomDialog::~CustomDialog()
{
	delete ui;
}

void CustomDialog::openDialog()
{
	isNeedSet = false;
	this->exec();
}

void CustomDialog::inputDone()
{
	isNeedSet = true;
	this->close();
}

bool CustomDialog::getIsNeedSet()
{
	return isNeedSet;
}

int CustomDialog::getInputRows()
{
	return ui->widthSpinBox->value();
}

int CustomDialog::getInputCols()
{
	return ui->heightSpinBox->value();
}

int CustomDialog::getInputMineCount()
{
	if (ui->mineSpinBox->value() >= ui->widthSpinBox->value() * ui->heightSpinBox->value())
	{
		return ui->widthSpinBox->value() * ui->heightSpinBox->value();
	}
	else { return ui->mineSpinBox->value(); }
}
