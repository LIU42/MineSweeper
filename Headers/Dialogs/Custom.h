#ifndef __DIALOGS_CUSTOM_H__
#define __DIALOGS_CUSTOM_H__

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
        bool isNeedSet;

    public:
        CustomDialog(QWidget* parent = nullptr);
        ~CustomDialog();

    public:
        void showDialog();
        void closeDialog();

    public:
        bool getIsNeedSet();
        int getInputRows();
        int getInputCols();
        int getInputMineCount();
};
#endif
