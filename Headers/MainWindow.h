#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QApplication>
#include <QMainWindow>
#include <QMouseEvent>
#include <QSoundEffect>
#include <QTimer>
#include <QStyle>
#include <QScreen>

#include "Games/MainGame.h"
#include "Dialogs/About.h"
#include "Dialogs/Custom.h"
#include "Dialogs/Record.h"
#include "Dialogs/Success.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class GameTimers
{
    private:
        static constexpr int FRAME_INTERVAL = 100;
        static constexpr int CLOCK_INTERVAL = 1000;

    public:
        QTimer* pFrameTimer;
        QTimer* pClockTimer;

    public:
        GameTimers();
        ~GameTimers();
};

class GameAudio
{
    public:
        QSoundEffect* pClickSound;
        QSoundEffect* pFailureSound;
        QSoundEffect* pSuccessSound;

    public:
        GameAudio();
        ~GameAudio();
};

class GameDialogs
{
    public:
        AboutDialog* pAboutDialog;
        CustomDialog* pCustomDialog;
        RecordDialog* pRecordDialog;
        SuccessDialog* pSuccessDialog;

    public:
        GameDialogs(QWidget* parent = nullptr);
        ~GameDialogs();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        static constexpr int MARGIN_X = 10;
        static constexpr int MARGIN_Y = 74;

    private:
        Ui::MainWindow* ui;

    private:
        MainGame* pMainGame;
        GameTimers* pTimers;
        GameAudio* pAudio;
        GameDialogs* pDialogs;

    private:
        int screenWidth;
        int screenHeight;
        int elapseTime;

    private:
        void setGameEasyLevel();
        void setGameNormalLevel();
        void setGameHighLevel();
        void setGameCustomLevel();
        void resizeWindow();

    private:
        void mainInterval();
        void clockCallback();
        void connectTimer();
        void connectAction();

    private:
        void restartGame();
        void pauseGame();
        void gameoverSuccess();
        void pauseIfMinimized();
        void uncoverEmptyBlocks();
        void updateGameInfo();

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
