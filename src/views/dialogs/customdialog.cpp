#include "views/dialogs/customdialog.h"

#include "ui_customdialog.h"

CustomDialog::CustomDialog(QWidget* parent) : QDialog(parent), ui(new Ui::CustomDialog)
{
    ui->setupUi(this);

    connect(ui->pDoneButton, &QPushButton::clicked, this, [=]
    {
        close();
    });
}

CustomDialog::~CustomDialog()
{
    delete ui;
}

void CustomDialog::show()
{
    needSet = false;
    QDialog::exec();
}

void CustomDialog::close()
{
    needSet = true;
    QDialog::close();
}

bool CustomDialog::isNeedSet()
{
    return needSet;
}

int CustomDialog::getInputRows()
{
    return ui->pRowsSpinBox->value();
}

int CustomDialog::getInputCols()
{
    return ui->pColsSpinBox->value();
}

int CustomDialog::getInputMineCount()
{
    if (ui->pMineSpinBox->value() >= ui->pRowsSpinBox->value() * ui->pColsSpinBox->value())
    {
        return ui->pRowsSpinBox->value() * ui->pColsSpinBox->value() - 1;
    }
    return ui->pMineSpinBox->value();
}
