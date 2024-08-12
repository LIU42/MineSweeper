#ifndef __VIEWS_DIALOGS_ABOUTDIALOG_H__
#define __VIEWS_DIALOGS_ABOUTDIALOG_H__

#include <QDialog>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class AboutDialog;
}

QT_END_NAMESPACE

class AboutDialog : public QDialog
{
    Q_OBJECT

    private:
        Ui::AboutDialog* ui;

    public:
        AboutDialog(QWidget* parent = nullptr);
        ~AboutDialog();
};
#endif