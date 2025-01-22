#ifndef __VIEWS_DIALOGS_SUCCESSDIALOG_H__
#define __VIEWS_DIALOGS_SUCCESSDIALOG_H__

#include <QDialog>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class SuccessDialog;
}

QT_END_NAMESPACE

class SuccessDialog : public QDialog
{
    Q_OBJECT

    private:
        Ui::SuccessDialog* ui;

    public:
        SuccessDialog(QWidget* parent = nullptr);
        ~SuccessDialog();

    public:
        QString getInputName();
};
#endif
