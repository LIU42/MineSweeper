#include "ui_about.h"
#include "ui_custom.h"
#include "ui_record.h"
#include "ui_success.h"

#include "dialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

CustomDialog::CustomDialog(QWidget *parent) : QDialog(parent), ui(new Ui::CustomDialog)
{
    ui->setupUi(this);
    connect(ui->doneButton, &QPushButton::clicked, this, &CustomDialog::inputDone);
}

CustomDialog::~CustomDialog()
{
    delete ui;
}

bool CustomDialog::getIfNeedSet()
{
	return ifNeedSet;
}

void CustomDialog::initDialog()
{
    ifNeedSet = false;
    this->exec();
}

void CustomDialog::inputDone()
{
    ifNeedSet = true;
    this->close();
}

int CustomDialog::getInputRows()
{
    return ui->widthSpinBox->value();
}

int CustomDialog::getInputCols()
{
    return ui->heightSpinBox->value();
}

int CustomDialog::getInputMineCount()
{
    if (ui->mineSpinBox->value() >= ui->widthSpinBox->value() * ui->heightSpinBox->value())
    {
        return ui->widthSpinBox->value() * ui->heightSpinBox->value();
    }
    else { return ui->mineSpinBox->value(); }
}

RecordDialog::RecordDialog(QWidget *parent) : QDialog(parent), ui(new Ui::RecordDialog)
{
    ui->setupUi(this);
    initRecord();
}

RecordDialog::~RecordDialog()
{
    delete ui;
}

bool RecordDialog::compare(Record record1, Record record2)
{
    return record1.time < record2.time;
}

void RecordDialog::initRecord()
{
    memset(recordCount, 0, sizeof(recordCount));

    for (int level = EASY_LEVEL; level <= HIGH_LEVEL; level++)
    {
        for (int i = 0; i < RECORD_COUNT; i++)
        {
			static QRect labelRect;

			labelRect.setX(RECORD_LABEL_LEFT + RECORD_LABEL_LEFT_STEP * level);
			labelRect.setY(RECORD_LABEL_TOP + RECORD_LABEL_TOP_STEP * i);
			labelRect.setWidth(RECORD_LABEL_WIDTH);
			labelRect.setHeight(RECORD_LABEL_HEIGHT);

            recordLabel[level][i] = new QLabel(this);
			recordLabel[level][i]->setGeometry(labelRect);
        }
    }
}

void RecordDialog::initDialog()
{
    static char text[INFO_MAX_LEN];

    for (int level = EASY_LEVEL; level <= HIGH_LEVEL; level++)
    {
		for (int i = 0; i < RECORD_COUNT; i++)
        {
            sprintf(text, "%ds (%s)", record[level][i].time, record[level][i].name.toStdString().data());
            recordLabel[level][i]->setText((i < recordCount[level]) ? text : "~");
        }
    }
    this->exec();
}

void RecordDialog::getRecord(QString name, int time, int level)
{
    if (recordCount[level] < RECORD_COUNT)
    {
        record[level][recordCount[level]].name = name;
        record[level][recordCount[level]].time = time;
        recordCount[level] += 1;
    }
    else if (time < record[level][RECORD_COUNT - 1].time)
    {
        record[level][RECORD_COUNT - 1].name = name;
        record[level][RECORD_COUNT - 1].time = time;
    }
    std::sort(record[level], record[level] + recordCount[level], compare);
}

SuccessDialog::SuccessDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SuccessDialog)
{
    ui->setupUi(this);
    connect(ui->donePushButton, &QPushButton::clicked, this, &SuccessDialog::inputDone);
}

SuccessDialog::~SuccessDialog()
{
    delete ui;
}

bool SuccessDialog::getIfNeedSave()
{
	return ifNeedSave;
}

void SuccessDialog::initDialog()
{
    ifNeedSave = false;
    this->exec();
}

void SuccessDialog::inputDone()
{
    ifNeedSave = true;
    this->close();
}

QString SuccessDialog::getInputName()
{
    return ui->nameLineEdit->text();
}
