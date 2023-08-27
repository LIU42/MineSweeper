#ifndef __DIALOGS_RECORD_H__
#define __DIALOGS_RECORD_H__

#include <QDialog>
#include <QLabel>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class RecordDialog;
}

QT_END_NAMESPACE

class RecordLabel : public QLabel
{
    friend class RecordDialog;

    public:
        static const int WIDTH = 160;
        static const int HEIGHT = 20;
        static const int INIT_POSITION_X = 50;
        static const int INIT_POSITION_Y = 90;
        static const int DISTANCE_X = 200;
        static const int DISTANCE_Y = 45;

    private:
        QString name;

    private:
        bool isHaveRecord;
        int time;

    public:
        RecordLabel(QWidget* parent = nullptr);

    public:
        void setGeometry(int, int);
        void setRecordInfo(QString&, int);
        void copyRecord(RecordLabel*);
        void updateRecordText();
};

class RecordDialog : public QDialog
{
    Q_OBJECT

    private:
        static const int LEVEL_COUNT = 3;
        static const int RECORD_COUNT = 3;

    private:
        Ui::RecordDialog* ui;
        RecordLabel* pLabelMatrix[LEVEL_COUNT][RECORD_COUNT];

    private:
        void setDialogFlags();
        void initLabelMatrix();

    public:
        RecordDialog(QWidget* parent = nullptr);
        ~RecordDialog();

    public:
        void addRecord(QString, int, int);
        void showDialog();
};
#endif