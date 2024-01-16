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
    private:
        static constexpr int WIDTH = 128;
        static constexpr int HEIGHT = 16;

    private:
        static constexpr int INIT_POSITION_X = 40;
        static constexpr int INIT_POSITION_Y = 72;

    private:
        static constexpr int DISTANCE_X = 160;
        static constexpr int DISTANCE_Y = 36;

    public:
        QString recordName;

    public:
        bool isHaveRecord;
        int recordTime;

    public:
        RecordLabel(int levelIndex, int recordIndex, QWidget* parent = nullptr);

    public:
        void operator=(RecordLabel& recordLabel);

    public:
        void setRecordInfo(QString& recordName, int recordTime);
        void updateRecordText();
};

class RecordDialog : public QDialog
{
    Q_OBJECT

    private:
        static constexpr int LEVEL_COUNT = 3;
        static constexpr int RECORD_COUNT = 3;

    private:
        Ui::RecordDialog* ui;

    private:
        RecordLabel* pLabelMatrix[LEVEL_COUNT][RECORD_COUNT];

    public:
        RecordDialog(QWidget* parent = nullptr);
        ~RecordDialog();

    public:
        void addRecord(QString recordName, int recordTime, int levelIndex);
        void showDialog();
};
#endif