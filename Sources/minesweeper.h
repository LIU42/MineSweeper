#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include <QMainWindow>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include <QMediaPlayer>
#include <QStyle>
#include <QScreen>

#include "config.h"
#include "dialog.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainGame;
}

QT_END_NAMESPACE

struct Point
{
    int x;
    int y;
};

struct Block
{
    int type;
    int number;
    bool isCovered;
    bool isMarked;
    bool isError;
    bool isTouched;
};

struct Image
{
    QPixmap block;
    QPixmap cover;
    QPixmap error;
    QPixmap mine;
    QPixmap mineError;
    QPixmap flag;
    QPixmap number[NUMBER_COUNT];
};

struct Timer
{
    QTimer interval;
    QTimer clock;
};

struct Color
{
    QColor white;
    QColor gray;
    QColor black;
};

struct Audio
{
    QMediaPlayer click;
    QMediaPlayer lose;
    QMediaPlayer win;
};

class MainGame : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::MainGame* ui;
        QPoint mouse;
        Image image;
        Timer timer;
        Color color;
        Audio audio;

    private:
        AboutDialog about;
        CustomDialog custom;
        SuccessDialog success;
        RecordDialog record;

    private:
		Block blockData[TABLE_ROWS_MAX][TABLE_COLS_MAX];
		QVector <Point> mineList;

    private:
        int screenWidth;
        int screenHeight;
        int tableWidth;
        int tableHeight;
        int tableRows;
        int tableCols;
        int mineInitCount;

    private:
        int status;
        int flagCount;
        int timeSec;
        int level;
        bool isCracked;
        bool ifHaveCracked;

    public:
        MainGame(QWidget *parent = nullptr);
        ~MainGame();

    public:
        void setEasyLevel();
        void setNormalLevel();
        void setHighLevel();
        void setCustomLevel();
        void resizeWindow();

    public:
        void loadImage();
        void loadAudio();
        void mainInterval();
        void clockCallback();
        void initGame();
        void initColor();
        void setInterval();
        void connectTimer();
        void connectAction();
        void startTimer();

    public:
        void addMine();
        void addNumber();
        void setRecord();
        void setPauseStatus();
        void gameoverWin();
        void gameoverLose(int, int);
        void update();

	public:
        void mousePressEvent(QMouseEvent*);
        void keyPressEvent(QKeyEvent*);
        void keyReleaseEvent(QKeyEvent*);
        void displayBackground(QPainter&);
        void displayBlock(QPainter&);
        void displayInfo(QPainter&);
        void paintEvent(QPaintEvent*);
};

#endif
