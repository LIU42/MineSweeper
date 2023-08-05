#include "success.h"
#include "ui_success.h"

SuccessDialog::SuccessDialog(QWidget* parent) : QDialog(parent), ui(new Ui::SuccessDialog)
{
    ui->setupUi(this);
    setDialogFlags();
    connectButtons();
}

SuccessDialog::~SuccessDialog()
{
    delete ui;
}

void SuccessDialog::setDialogFlags()
{
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

void SuccessDialog::connectButtons()
{
    connect(ui->pDoneButton, &QPushButton::clicked, this, &SuccessDialog::colseDialog);
}

void SuccessDialog::showDialog()
{
    isNeedSave = false;
    QDialog::exec();
}

void SuccessDialog::colseDialog()
{
    isNeedSave = true;
    QDialog::close();
}

bool SuccessDialog::getIsNeedSave()
{
    return isNeedSave;
}

QString SuccessDialog::getInputName()
{
    return ui->pNameLineEdit->text();
}
