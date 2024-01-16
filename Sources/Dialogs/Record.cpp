#include "Dialogs/Record.h"
#include "ui_Record.h"

RecordLabel::RecordLabel(int levelIndex, int recordIndex, QWidget* parent): QLabel(parent)
{
    int x = INIT_POSITION_X + DISTANCE_X * levelIndex;
    int y = INIT_POSITION_Y + DISTANCE_Y * recordIndex;

    isHaveRecord = false;
    setGeometry(x, y, WIDTH, HEIGHT);
}

void RecordLabel::operator=(RecordLabel& recordLabel)
{
    isHaveRecord = recordLabel.isHaveRecord;
    recordName = recordLabel.recordName;
    recordTime = recordLabel.recordTime;
}

void RecordLabel::setRecordInfo(QString& recordName, int recordTime)
{
    this->isHaveRecord = true;
    this->recordName = recordName;
    this->recordTime = recordTime;
}

void RecordLabel::updateRecordText()
{
    setText((isHaveRecord) ? QString("%1s (%2)").arg(recordTime).arg(recordName) : "~");
}

RecordDialog::RecordDialog(QWidget* parent): QDialog(parent), ui(new Ui::RecordDialog)
{
    for (int levelIndex = 0; levelIndex < LEVEL_COUNT; levelIndex++)
    {
        for (int recordIndex = 0; recordIndex < RECORD_COUNT; recordIndex++)
        {
            pLabelMatrix[levelIndex][recordIndex] = new RecordLabel(levelIndex, recordIndex, this);
        }
    }
    ui->setupUi(this);
}

RecordDialog::~RecordDialog()
{
    for (int levelIndex = 0; levelIndex < LEVEL_COUNT; levelIndex++)
    {
        for (int recordIndex = 0; recordIndex < RECORD_COUNT; recordIndex++)
        {
            delete pLabelMatrix[levelIndex][recordIndex];
        }
    }
    delete ui;
}

void RecordDialog::addRecord(QString name, int time, int levelIndex)
{
    for (int insertIndex = 0; insertIndex < RECORD_COUNT; insertIndex++)
    {
        if (time >= pLabelMatrix[levelIndex][insertIndex]->recordTime && pLabelMatrix[levelIndex][insertIndex]->isHaveRecord)
        {
            continue;
        }
        for (int i = RECORD_COUNT - 2; i >= insertIndex; i--)
        {
            *pLabelMatrix[levelIndex][i + 1] = *pLabelMatrix[levelIndex][i];
        }
        pLabelMatrix[levelIndex][insertIndex]->setRecordInfo(name, time);
        return;
    }
}

void RecordDialog::showDialog()
{
    for (int levelIndex = 0; levelIndex < LEVEL_COUNT; levelIndex++)
    {
        for (int recordIndex = 0; recordIndex < RECORD_COUNT; recordIndex++)
        {
            pLabelMatrix[levelIndex][recordIndex]->updateRecordText();
        }
    }
    exec();
}