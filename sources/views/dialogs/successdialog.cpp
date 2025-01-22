#include "views/dialogs/successdialog.h"

#include "ui_successdialog.h"

SuccessDialog::SuccessDialog(QWidget* parent) : QDialog(parent), ui(new Ui::SuccessDialog)
{
    ui->setupUi(this);

    connect(ui->doneButton, &QPushButton::clicked, this, [=]
    {
        close();
    });
}

SuccessDialog::~SuccessDialog()
{
    delete ui;
}

QString SuccessDialog::getInputName()
{
    return ui->nameLineEdit->text();
}
