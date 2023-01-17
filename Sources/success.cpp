#include "success.h"
#include "ui_success.h"

SuccessDialog::SuccessDialog(QWidget* parent) : QDialog(parent), ui(new Ui::SuccessDialog)
{
    ui->setupUi(this);
	setWindowFlag(Qt::WindowContextHelpButtonHint, false);
	connect(ui->donePushButton, &QPushButton::clicked, this, &SuccessDialog::inputDone);
}

SuccessDialog::~SuccessDialog()
{
    delete ui;
}

void SuccessDialog::openDialog()
{
	isNeedSave = false;
    this->exec();
}

void SuccessDialog::inputDone()
{
	isNeedSave = true;
    this->close();
}

bool SuccessDialog::getIsNeedSave()
{
	return isNeedSave;
}

QString SuccessDialog::getInputName()
{
    return ui->nameLineEdit->text();
}
