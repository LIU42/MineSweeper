#include "utils/constants.h"
#include "views/dialogs/rankdialog.h"

#include "ui_rankdialog.h"

RankDialog::RankDialog(QWidget* parent): QDialog(parent), ui(new Ui::RecordDialog)
{
    ui->setupUi(this);

    ui->tableWidget1->setColumnWidth(0, RecordProperties::NAME_WIDTH);
    ui->tableWidget1->setColumnWidth(1, RecordProperties::TIME_WIDTH);

    ui->tableWidget2->setColumnWidth(0, RecordProperties::NAME_WIDTH);
    ui->tableWidget2->setColumnWidth(1, RecordProperties::TIME_WIDTH);

    ui->tableWidget3->setColumnWidth(0, RecordProperties::NAME_WIDTH);
    ui->tableWidget3->setColumnWidth(1, RecordProperties::TIME_WIDTH);
}

RankDialog::~RankDialog()
{
    delete ui;
}

void RankDialog::addRecord(QString name, QString time, int level)
{
    QTableWidget* tableWidget = nullptr;

    switch (level)
    {
        case GameLevel::LEVEL1: tableWidget = ui->tableWidget1; break;
        case GameLevel::LEVEL2: tableWidget = ui->tableWidget2; break;
        case GameLevel::LEVEL3: tableWidget = ui->tableWidget3; break;
    }
    tableWidget->insertRow(0);

    QTableWidgetItem* nameItem = new QTableWidgetItem(name);
    QTableWidgetItem* timeItem = new QTableWidgetItem(time);

    nameItem->setTextAlignment(Qt::AlignCenter);
    timeItem->setTextAlignment(Qt::AlignCenter);

    tableWidget->setItem(0, 0, nameItem);
    tableWidget->setItem(0, 1, timeItem);

    tableWidget->sortByColumn(1, Qt::AscendingOrder);
}
