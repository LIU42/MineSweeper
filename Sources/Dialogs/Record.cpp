#include "Dialogs/Record.h"
#include "ui_Record.h"

RecordLabel::RecordLabel(QWidget* parent): QLabel(parent)
{
    isHaveRecord = false;
}

void RecordLabel::setGeometry(int levelIndex, int recordIndex)
{
    int x = INIT_POSITION_X + DISTANCE_X * levelIndex;
    int y = INIT_POSITION_Y + DISTANCE_Y * recordIndex;

    QLabel::setGeometry(x, y, WIDTH, HEIGHT);
}

void RecordLabel::setRecordInfo(QString& name, int time)
{
    this->isHaveRecord = true;
    this->name = name;
    this->time = time;
}

void RecordLabel::copyRecord(RecordLabel* pRecordLabel)
{
    isHaveRecord = pRecordLabel->isHaveRecord;
    name = pRecordLabel->name;
    time = pRecordLabel->time;
}

void RecordLabel::updateRecordText()
{
    setText((isHaveRecord) ? QString("%1s (%2)").arg(time).arg(name) : "~");
}

RecordDialog::RecordDialog(QWidget* parent): QDialog(parent), ui(new Ui::RecordDialog)
{
    ui->setupUi(this);
    setDialogFlags();
    initLabelMatrix();
}

RecordDialog::~RecordDialog()
{
    delete ui;
}

void RecordDialog::setDialogFlags()
{
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

void RecordDialog::initLabelMatrix()
{
    for (int levelIndex = 0; levelIndex < LEVEL_COUNT; levelIndex++)
    {
        for (int recordIndex = 0; recordIndex < RECORD_COUNT; recordIndex++)
        {
            pLabelMatrix[levelIndex][recordIndex] = new RecordLabel(this);
            pLabelMatrix[levelIndex][recordIndex]->setGeometry(levelIndex, recordIndex);
        }
    }
}

void RecordDialog::addRecord(QString name, int time, int levelIndex)
{
    for (int insertIndex = 0; insertIndex < RECORD_COUNT; insertIndex++)
    {
        if (time >= pLabelMatrix[levelIndex][insertIndex]->time && pLabelMatrix[levelIndex][insertIndex]->isHaveRecord)
        {
            continue;
        }
        for (int i = RECORD_COUNT - 2; i >= insertIndex; i--)
        {
            pLabelMatrix[levelIndex][i + 1]->copyRecord(pLabelMatrix[levelIndex][i]);
        }
        return pLabelMatrix[levelIndex][insertIndex]->setRecordInfo(name, time);
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
    QDialog::exec();
}