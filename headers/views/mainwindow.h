#ifndef __VIEWS_MAINWINDOW_H__
#define __VIEWS_MAINWINDOW_H__

#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>
#include <QStyle>
#include <QScreen>

#include "cores/framework.h"
#include "utils/resources.h"

#include "views/dialogs/aboutdialog.h"
#include "views/dialogs/customdialog.h"
#include "views/dialogs/rankdialog.h"
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
        GameFramework* gameFramework;
        GameResources* gameResources;

    private:
        QTimer* frameTimer;
        QTimer* clockTimer;

    private:
        AboutDialog* aboutDialog;
        CustomDialog* customDialog;
        RankDialog* rankDialog;
        SuccessDialog* successDialog;

    private:
        int fitnessW;
        int fitnessH;
        int elapseTime;

    private:
        void setLevel1();
        void setLevel2();
        void setLevel3();
        void setCustomLevel();

    private:
        void setupTimers();
        void setupActions();

    private:
        void resizeWindow();
        void restartGame();
        void judgeSuccess();
        void updateInfo();

    private:
        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent* event) override;

    private:
        void mousePressEvent(QMouseEvent* event) override;

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    public:
        void initialize();
};
#endif
