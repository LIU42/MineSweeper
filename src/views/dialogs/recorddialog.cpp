#include "views/dialogs/recorddialog.h"

#include "ui_recorddialog.h"

void RecordSlot::operator=(RecordSlot& slot)
{
    this->enable = slot.enable;
    this->name = slot.name;
    this->time = slot.time;
}

void RecordSlot::init()
{
    this->enable = false;
}

void RecordSlot::setRecord(QString name, int time)
{
    this->enable = true;
    this->name = name;
    this->time = time;
}

QString RecordSlot::getText()
{
    return (enable) ? QString("%1s (%2)").arg(time).arg(name) : "~";
}

bool RecordSlot::isEnable()
{
    return enable;
}

int RecordSlot::getTime()
{
    return time;
}

RecordDialog::RecordDialog(QWidget* parent): QDialog(parent), ui(new Ui::RecordDialog)
{
    ui->setupUi(this);

    for (int level = 0; level < GameLevel::COUNT; level++)
    {
        for (int recordIndex = 0; recordIndex < RecordProperties::RECORD_COUNT; recordIndex++)
        {
            recordSlots[level][recordIndex].init();
        }
    }
}

RecordDialog::~RecordDialog()
{
    delete ui;
}

void RecordDialog::addRecord(QString name, int time, int level)
{
    for (int insertIndex = 0; insertIndex < RecordProperties::RECORD_COUNT; insertIndex++)
    {
        if (recordSlots[level][insertIndex].isEnable() && time >= recordSlots[level][insertIndex].getTime())
        {
            continue;
        }
        for (int index = RecordProperties::RECORD_COUNT - 2; index >= insertIndex; index--)
        {
            recordSlots[level][index + 1] = recordSlots[level][index];
        }
        recordSlots[level][insertIndex].setRecord(name, time);
        return;
    }
}

void RecordDialog::show()
{
    ui->pRecord11->setText(recordSlots[GameLevel::LEVEL1][0].getText());
    ui->pRecord12->setText(recordSlots[GameLevel::LEVEL1][1].getText());
    ui->pRecord13->setText(recordSlots[GameLevel::LEVEL1][2].getText());

    ui->pRecord21->setText(recordSlots[GameLevel::LEVEL2][0].getText());
    ui->pRecord22->setText(recordSlots[GameLevel::LEVEL2][1].getText());
    ui->pRecord23->setText(recordSlots[GameLevel::LEVEL2][2].getText());

    ui->pRecord31->setText(recordSlots[GameLevel::LEVEL3][0].getText());
    ui->pRecord32->setText(recordSlots[GameLevel::LEVEL3][1].getText());
    ui->pRecord33->setText(recordSlots[GameLevel::LEVEL3][2].getText());

    QDialog::exec();
}