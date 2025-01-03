#ifndef __DIALOGS_SUCCESS_H__
#define __DIALOGS_SUCCESS_H__

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

    private:
        bool needSave;

    public:
        SuccessDialog(QWidget* parent = nullptr);
        ~SuccessDialog();

    public:
        void show();
        void close();

    public:
        QString getInputName();

    public:
        bool isNeedSave();
};
#endif
