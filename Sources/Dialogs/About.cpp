#include "Dialogs/About.h"
#include "ui_About.h"

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent), ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setDialogFlags();
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::setDialogFlags()
{
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}
