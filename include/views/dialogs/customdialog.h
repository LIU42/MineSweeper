#ifndef __VIEWS_DIALOGS_CUSTOMDIALOG_H__
#define __VIEWS_DIALOGS_CUSTOMDIALOG_H__

#include <QDialog>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class CustomDialog;
}

QT_END_NAMESPACE

class CustomDialog : public QDialog
{
    Q_OBJECT

    private:
        Ui::CustomDialog* ui;

    private:
        bool needSet;

    public:
        CustomDialog(QWidget* parent = nullptr);
        ~CustomDialog();

    public:
        void show();
        void close();

    public:
        bool isNeedSet();
        int getInputRows();
        int getInputCols();
        int getInputMineCount();
};
#endif