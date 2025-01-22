#include "views/dialogs/customdialog.h"

#include "ui_customdialog.h"

CustomDialog::CustomDialog(QWidget* parent) : QDialog(parent), ui(new Ui::CustomDialog)
{
    ui->setupUi(this);

    connect(ui->doneButton, &QPushButton::clicked, this, [=]
    {
        close();
    });
}

CustomDialog::~CustomDialog()
{
    delete ui;
}

int CustomDialog::getInputRows()
{
    return ui->rowsSpinBox->value();
}

int CustomDialog::getInputCols()
{
    return ui->colsSpinBox->value();
}

int CustomDialog::getInputMineCount()
{
    if (ui->mineSpinBox->value() >= ui->rowsSpinBox->value() * ui->colsSpinBox->value())
    {
        return ui->rowsSpinBox->value() * ui->colsSpinBox->value() - 1;
    }
    return ui->mineSpinBox->value();
}
