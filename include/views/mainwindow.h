#ifndef __VIEWS_MAINWINDOW_H__
#define __VIEWS_MAINWINDOW_H__

#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>
#include <QStyle>
#include <QScreen>

#include "commons/resources.h"
#include "cores/controller.h"

#include "views/dialogs/aboutdialog.h"
#include "views/dialogs/customdialog.h"
#include "views/dialogs/recorddialog.h"
#include "views/dialogs/successdialog.h"


QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::MainWindow* ui;

    private:
        GameController* pGameController;
        GameResources* pGameResources;

    private:
        QTimer* pFrameTimer;
        QTimer* pClockTimer;

    private:
        AboutDialog* pAboutDialog;
        CustomDialog* pCustomDialog;
        RecordDialog* pRecordDialog;
        SuccessDialog* pSuccessDialog;

    private:
        int windowWidth;
        int windowHeight;
        int elapseTime;

    private:
        void setLevel1();
        void setLevel2();
        void setLevel3();
        void setCustomLevel();
        void resizeWindow();

    private:
        void setupTimers();
        void setupActions();

    private:
        void restart();
        void judgeSuccess();
        void updateInfo();

    private:
        void mousePressEvent(QMouseEvent* pMouseEvent) override;
        void keyPressEvent(QKeyEvent* pKeyEvent) override;
        void keyReleaseEvent(QKeyEvent* pKeyEvent) override;

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    public:
        void init();
};
#endif
