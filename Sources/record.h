#ifndef __RECORD_H__
#define __RECORD_H__

#include <QDialog>
#include <QLabel>

QT_BEGIN_NAMESPACE

namespace Ui
{
	class RecordDialog;
}

QT_END_NAMESPACE

enum Level { EASY, NORMAL, HIGH, CUSTOM };

enum LabelConstant
{
	WIDTH = 160,
	HEIGHT = 20,
	INIT_LEFT = 50,
	INIT_UPPER = 90,
	DISTANCE_LEFT = 200,
	DISTANCE_UPPER = 45
};

struct Record
{
	QString name;
	int time;
};

class RecordDialog : public QDialog
{
	Q_OBJECT

	private:
		static const int LEVEL_COUNT = 3;
		static const int RECORD_COUNT = 3;

	private:
		Ui::RecordDialog* ui;
		QLabel* pRecordLabels[LEVEL_COUNT][RECORD_COUNT];

	private:
		Record record[LEVEL_COUNT][RECORD_COUNT];
		int recordCount[LEVEL_COUNT];

	private:
		static bool compare(Record&, Record&);

	private:
		void setDialogFlags();
		void initDialog();

	public:
		RecordDialog(QWidget* parent = nullptr);
		~RecordDialog();

	public:
		void openDialog();
		void getRecord(QString, int, Level);
};
#endif
