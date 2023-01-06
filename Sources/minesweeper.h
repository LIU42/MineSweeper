#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include <QApplication>
#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include <QMediaPlayer>
#include <QDateTime>
#include <QStyle>
#include <QScreen>

#include "about.h"
#include "custom.h"
#include "record.h"
#include "success.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainGame;
}

QT_END_NAMESPACE

enum Status { PLAYING, PAUSE, OVER, WIN, EXIT };
enum BlockType { EMPTY, NUMBER, MINE };

enum ImageConstant
{
	NUMBER_COUNT = 8
};

enum ColorConstant
{
	WHITE = 0xFFFFFFFF,
	BLACK = 0xFF353535,
	GRAY = 0xFF606060
};

enum class EasyLevel
{
	ROWS = 10,
	COLS = 10,
	MINE_INIT_COUNT = 10
};

enum class NormalLevel
{
	ROWS = 15,
	COLS = 15,
	MINE_INIT_COUNT = 30
};

enum class HighLevel
{
	ROWS = 30,
	COLS = 20,
	MINE_INIT_COUNT = 100
};

struct Block
{
	BlockType type;
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
		static const int GAME_FPS = 10;
		static const int CLOCK_INTERVAL = 1000;

	private:
		static const int ROWS_MAX = 40;
		static const int COLS_MAX = 25;
		static const int MINE_COUNT_MAX = 1000;

	private:
		static const int BLOCK_SIZE = 32;
		static const int MARGIN_X = 12;
		static const int MARGIN_Y = 78;
		static const int BORDER = 6;
		static const int BLOCK_BORDER = 1;

	private:
		static const int INFO_TOP = 53;
		static const int INFO_LENGTH = 30;
		static const int INFO_WIDTH = 120;

    private:
        Ui::MainGame* ui;
        QPoint mouse;
        Image image;
        Timer timer;
        Color color;
        Audio audio;

    private:
		AboutDialog* about;
		CustomDialog* custom;
		SuccessDialog* success;
		RecordDialog* record;

    private:
		Block blocks[ROWS_MAX][COLS_MAX];
		QVector <QPoint> mines;

    private:
        int screenWidth;
        int screenHeight;
        int tableWidth;
        int tableHeight;
        int tableRows;
        int tableCols;
        int mineInitCount;

    private:
		Status status;
		Level level;
        int flagCount;
		int timeDuring;
        bool isCracked;
		bool isHaveCracked;

	private:
        void setEasyLevel();
        void setNormalLevel();
        void setHighLevel();
        void setCustomLevel();
        void resizeWindow();

	private:
        void loadImage();
        void loadAudio();
        void mainInterval();
        void clockCallback();
        void initColor();
        void setInterval();
        void connectTimer();
        void connectAction();
        void startTimer();

	private:
		void restart();
        void addMine();
        void addNumber();
        void setRecord();
		void setPause();
        void gameoverWin();
        void gameoverLose(int, int);
        void update();

	private:
        void mousePressEvent(QMouseEvent*);
        void keyPressEvent(QKeyEvent*);
        void keyReleaseEvent(QKeyEvent*);

	private:
        void displayBackground(QPainter&);
        void displayBlock(QPainter&);
        void displayInfo(QPainter&);
        void paintEvent(QPaintEvent*);

	public:
		MainGame(QWidget *parent = nullptr);
		~MainGame();

	public:
		void init();
};
#endif
