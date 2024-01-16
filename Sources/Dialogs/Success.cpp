#include "Dialogs/Success.h"
#include "ui_Success.h"

SuccessDialog::SuccessDialog(QWidget* parent) : QDialog(parent), ui(new Ui::SuccessDialog)
{
    ui->setupUi(this);
    connect(ui->pDoneButton, &QPushButton::clicked, this, &SuccessDialog::colseDialog);
}

SuccessDialog::~SuccessDialog()
{
    delete ui;
}

void SuccessDialog::showDialog()
{
    isNeedSave = false;
    exec();
}

void SuccessDialog::colseDialog()
{
    isNeedSave = true;
    close();
}

QString SuccessDialog::getInputName()
{
    return ui->pNameLineEdit->text();
}

bool SuccessDialog::getIsNeedSave()
{
    return isNeedSave;
}
