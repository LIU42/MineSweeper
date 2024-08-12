#include "views/dialogs/successdialog.h"

#include "ui_successdialog.h"

SuccessDialog::SuccessDialog(QWidget* parent) : QDialog(parent), ui(new Ui::SuccessDialog)
{
    ui->setupUi(this);

    connect(ui->pDoneButton, &QPushButton::clicked, this, [=]
    {
        close();
    });
}

SuccessDialog::~SuccessDialog()
{
    delete ui;
}

void SuccessDialog::show()
{
    needSave = false;
    QDialog::exec();
}

void SuccessDialog::close()
{
    needSave = true;
    QDialog::close();
}

QString SuccessDialog::getInputName()
{
    return ui->pNameLineEdit->text();
}

bool SuccessDialog::isNeedSave()
{
    return needSave;
}
