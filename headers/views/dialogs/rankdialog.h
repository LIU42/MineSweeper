#ifndef __VIEWS_DIALOGS_RANKDIALOG_H__
#define __VIEWS_DIALOGS_RANKDIALOG_H__

#include <QDialog>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class RecordDialog;
}

QT_END_NAMESPACE

class RankDialog : public QDialog
{
    Q_OBJECT

    private:
        Ui::RecordDialog* ui;

    public:
        RankDialog(QWidget* parent = nullptr);
        ~RankDialog();

    public:
        void addRecord(QString name, QString time, int level);
};
#endif
