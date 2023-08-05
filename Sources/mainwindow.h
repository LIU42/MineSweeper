#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QApplication>
#include <QMainWindow>
#include <QMouseEvent>
#include <QSoundEffect>
#include <QTimer>
#include <QStyle>
#include <QScreen>

#include "Models/minesweeper.h"
#include "Dialogs/about.h"
#include "Dialogs/custom.h"
#include "Dialogs/record.h"
#include "Dialogs/success.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class GameTimers
{
    friend class MainWindow;

    private:
        static const int GAME_FPS = 10;
        static const int CLOCK_INTERVAL = 1000;

    private:
        QTimer interval;
        QTimer clock;
};

class GameAudio
{
    friend class MainWindow;

    private:
        QSoundEffect click;
        QSoundEffect failure;
        QSoundEffect success;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        static const int MARGIN_X = 12;
        static const int MARGIN_Y = 78;

    private:
        Ui::MainWindow* ui;
        MainGame* pGame;
        AboutDialog* pAboutDialog;
        CustomDialog* pCustomDialog;
        SuccessDialog* pSuccessDialog;
        RecordDialog* pRecordDialog;

    private:
        GameTimers timers;
        GameAudio audio;

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
        void loadAudio();
        void mainInterval();
        void clockCallback();
        void setInterval();
        void connectTimer();
        void connectAction();
        void startTimer();

    private:
        void gameRestart();
        void gamePause();
        void gameoverSuccess();
        void gameAutoPause();
        void gameAutoUncoverBlocks();
        void updateGameInfo();

    private:
        void mousePressEvent(QMouseEvent*);
        void keyPressEvent(QKeyEvent*);
        void keyReleaseEvent(QKeyEvent*);

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    public:
        void setGame(MainGame*);
        void init();
};
#endif
