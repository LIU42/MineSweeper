#ifndef __DIALOGS_RECORD_H__
#define __DIALOGS_RECORD_H__

#include <QDialog>

#include "commons/constants.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class RecordDialog;
}

QT_END_NAMESPACE

class RecordSlot
{
    private:
        QString name;

    private:
        bool enable;
        int time;

    public:
        void operator=(RecordSlot& record);

    public:
        void init();
        void setRecord(QString name, int time);

    public:
        QString getText();

    public:
        bool isEnable();
        int getTime();
};

class RecordDialog : public QDialog
{
    Q_OBJECT

    private:
        Ui::RecordDialog* ui;

    private:
        RecordSlot recordSlots[GameLevel::COUNT][RecordProperties::RECORD_COUNT];

    public:
        RecordDialog(QWidget* parent = nullptr);
        ~RecordDialog();

    public:
        void addRecord(QString name, int time, int level);
        void show();
};
#endif