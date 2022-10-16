#ifndef __DIALOG_H__
#define __DIALOG_H__

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QFont>

#include "config.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class AboutDialog;
    class CustomDialog;
    class RecordDialog;
    class SuccessDialog;
}

QT_END_NAMESPACE

struct Record
{
    QString name;
    int time;
};

class AboutDialog : public QDialog
{
    Q_OBJECT

    private:
        Ui::AboutDialog *ui;

    public:
        AboutDialog(QWidget *parent = nullptr);
        ~AboutDialog();
};

class CustomDialog : public QDialog
{
    Q_OBJECT

	private:
        Ui::CustomDialog *ui;
        bool ifNeedSet;

    public:
        CustomDialog(QWidget *parent = nullptr);
        ~CustomDialog();

    public:
		bool getIfNeedSet();
        void initDialog();
        void inputDone();
        int getInputRows();
        int getInputCols();
        int getInputMineCount();
};

class RecordDialog : public QDialog
{
    Q_OBJECT

    private:
        Ui::RecordDialog *ui;
        QLabel* recordLabel[LEVEL_COUNT][RECORD_COUNT];

	private:
        Record record[LEVEL_COUNT][RECORD_COUNT];
        int recordCount[RECORD_COUNT];

    public:
        RecordDialog(QWidget *parent = nullptr);
        ~RecordDialog();

    public:
        static bool compare(Record, Record);
        void initRecord();
        void initDialog();
        void getRecord(QString, int, int);
};

class SuccessDialog : public QDialog
{
    Q_OBJECT

	private:
        Ui::SuccessDialog *ui;
        bool ifNeedSave;

    public:
        SuccessDialog(QWidget *parent = nullptr);
        ~SuccessDialog();

    public:
		bool getIfNeedSave();
        void initDialog();
        void inputDone();
        QString getInputName();
};

#endif
