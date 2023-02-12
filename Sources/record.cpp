#include "record.h"
#include "ui_record.h"

RecordDialog::RecordDialog(QWidget* parent) : QDialog(parent), ui(new Ui::RecordDialog)
{
	ui->setupUi(this);
	setDialogFlags();
	initDialog();
}

RecordDialog::~RecordDialog()
{
	delete ui;
}

bool RecordDialog::compare(Record& record1, Record& record2)
{
	return record1.time < record2.time;
}

void RecordDialog::setDialogFlags()
{
	setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

void RecordDialog::initDialog()
{
	memset(recordCount, 0, sizeof(recordCount));

	for (int level = EASY; level <= HIGH; level++)
	{
		for (int i = 0; i < RECORD_COUNT; i++)
		{
			static QRect rect;

			rect.setX(INIT_X + DISTANCE_X * level);
			rect.setY(INIT_Y + DISTANCE_Y * i);
			rect.setWidth(WIDTH);
			rect.setHeight(HEIGHT);

			recordLabel[level][i] = new QLabel(this);
			recordLabel[level][i]->setGeometry(rect);
		}
	}
}

void RecordDialog::openDialog()
{
	static QString text;

	for (int level = EASY; level <= HIGH; level++)
	{
		for (int i = 0; i < RECORD_COUNT; i++)
		{
			text = QString("%1s (%2)").arg(record[level][i].time).arg(record[level][i].name);
			recordLabel[level][i]->setText((i < recordCount[level]) ? text : "~");
		}
	}
	this->exec();
}

void RecordDialog::getRecord(QString name, int time, Level level)
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
