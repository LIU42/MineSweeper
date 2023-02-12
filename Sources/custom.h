#ifndef __CUSTOM_H__
#define __CUSTOM_H__

#include <QDialog>

QT_BEGIN_NAMESPACE

namespace Ui
{
	class CustomDialog;
}

QT_END_NAMESPACE

class CustomDialog : public QDialog
{
	Q_OBJECT

	private:
		Ui::CustomDialog* ui;
		bool isNeedSet;

	private:
		void setDialogFlags();
		void connectSignals();

	public:
		CustomDialog(QWidget* parent = nullptr);
		~CustomDialog();

	public:
		void openDialog();
		void inputDone();

	public:
		bool getIsNeedSet();
		int getInputRows();
		int getInputCols();
		int getInputMineCount();
};
#endif
