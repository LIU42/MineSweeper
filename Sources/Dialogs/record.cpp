#include "record.h"
#include "ui_record.h"

RecordLabel::RecordLabel(QWidget* parent): QLabel(parent)
{
    isHaveRecord = false;
}

void RecordLabel::setGeometry(GameLevel level, int recordIndex)
{
    int x = INIT_POSITION_X + DISTANCE_X * level;
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
    for (int level = LEVEL_EASY; level <= LEVEL_HIGH; level++)
    {
        for (int recordIndex = 0; recordIndex < RECORD_COUNT; recordIndex++)
        {
            pLabelMatrix[level][recordIndex] = new RecordLabel(this);
            pLabelMatrix[level][recordIndex]->setGeometry((GameLevel)level, recordIndex);
        }
    }
}

void RecordDialog::addRecord(QString name, int time, GameLevel level)
{
    for (int insertIndex = 0; insertIndex < RECORD_COUNT; insertIndex++)
    {
        if (time >= pLabelMatrix[level][insertIndex]->time && pLabelMatrix[level][insertIndex]->isHaveRecord)
        {
            continue;
        }
        for (int i = RECORD_COUNT - 2; i >= insertIndex; i--)
        {
            pLabelMatrix[level][i + 1]->copyRecord(pLabelMatrix[level][i]);
        }
        return pLabelMatrix[level][insertIndex]->setRecordInfo(name, time);
    }
}

void RecordDialog::showDialog()
{
    for (int level = LEVEL_EASY; level <= LEVEL_HIGH; level++)
    {
        for (int recordIndex = 0; recordIndex < RECORD_COUNT; recordIndex++)
        {
            pLabelMatrix[level][recordIndex]->updateRecordText();
        }
    }
    QDialog::exec();
}