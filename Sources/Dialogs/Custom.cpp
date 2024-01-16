#include "Dialogs/Custom.h"
#include "ui_Custom.h"

CustomDialog::CustomDialog(QWidget* parent) : QDialog(parent), ui(new Ui::CustomDialog)
{
    ui->setupUi(this);
    connect(ui->pDoneButton, &QPushButton::clicked, this, &CustomDialog::closeDialog);
}

CustomDialog::~CustomDialog()
{
    delete ui;
}

void CustomDialog::showDialog()
{
    isNeedSet = false;
    exec();
}

void CustomDialog::closeDialog()
{
    isNeedSet = true;
    close();
}

bool CustomDialog::getIsNeedSet()
{
    return isNeedSet;
}

int CustomDialog::getInputRows()
{
    return ui->pWidthSpinBox->value();
}

int CustomDialog::getInputCols()
{
    return ui->pHeightSpinBox->value();
}

int CustomDialog::getInputMineCount()
{
    if (ui->pMineSpinBox->value() >= ui->pWidthSpinBox->value() * ui->pHeightSpinBox->value())
    {
        return ui->pWidthSpinBox->value() * ui->pHeightSpinBox->value() - 1;
    }
    return ui->pMineSpinBox->value();
}
