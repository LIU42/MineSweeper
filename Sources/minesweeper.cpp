#include "minesweeper.h"
#include "ui_minesweeper.h"

MainGame::MainGame(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainGame)
{
    ui->setupUi(this);
	about = new AboutDialog(this);
	custom = new CustomDialog(this);
	success = new SuccessDialog(this);
	record = new RecordDialog(this);
}

MainGame::~MainGame()
{
    delete ui;
	delete about;
	delete custom;
	delete success;
	delete record;
}

void MainGame::init()
{
	srand((unsigned)time(NULL));

	loadImage();
	loadAudio();
	initColor();
	setInterval();
	connectTimer();
	connectAction();
	startTimer();
	setEasyLevel();
}

void MainGame::loadImage()
{
	image.block.load(":/Images/block.png");
    image.cover.load(":/Images/cover.png");
    image.error.load(":/Images/error.png");
    image.mine.load(":/Images/mine.png");
    image.mineError.load(":/Images/mine_error.png");
    image.flag.load(":/Images/flag.png");

    for (int i = 0; i < NUMBER_COUNT; i++)
    {
		image.number[i].load(QString(":/Images/number_%1.png").arg(i + 1));
    }
}

void MainGame::loadAudio()
{
    audio.click.setMedia(QUrl("qrc:/Audio/click.mp3"));
    audio.lose.setMedia(QUrl("qrc:/Audio/lose.mp3"));
    audio.win.setMedia(QUrl("qrc:/Audio/win.mp3"));
}

void MainGame::setEasyLevel()
{
	level = EASY;
	tableRows = (int)EasyLevel::ROWS;
	tableCols = (int)EasyLevel::COLS;
	mineInitCount = (int)EasyLevel::MINE_INIT_COUNT;
    resizeWindow();
	restart();
}

void MainGame::setNormalLevel()
{
	level = NORMAL;
	tableRows = (int)NormalLevel::ROWS;
	tableCols = (int)NormalLevel::COLS;
	mineInitCount = (int)NormalLevel::MINE_INIT_COUNT;
    resizeWindow();
	restart();
}

void MainGame::setHighLevel()
{
	level = HIGH;
	tableRows = (int)HighLevel::ROWS;
	tableCols = (int)HighLevel::COLS;
	mineInitCount = (int)HighLevel::MINE_INIT_COUNT;
    resizeWindow();
	restart();
}

void MainGame::setCustomLevel()
{
	custom->openDialog();

	if (custom->getIsNeedSet())
    {
		level = CUSTOM;
		tableRows = custom->getInputRows();
		tableCols = custom->getInputCols();
		mineInitCount = custom->getInputMineCount();
        resizeWindow();
		restart();
	}
}

void MainGame::resizeWindow()
{
	tableWidth = tableRows * BLOCK_SIZE;
	tableHeight = tableCols * BLOCK_SIZE;
    screenWidth = MARGIN_X * 2 + tableWidth;
    screenHeight = MARGIN_X + MARGIN_Y + tableHeight;

    setFixedSize(screenWidth, screenHeight);
	setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), QGuiApplication::screens().at(0)->geometry()));
}

void MainGame::mainInterval()
{
    if (status == PLAYING)
    {
        MainGame::gameoverWin();
		MainGame::autoUncover();
    }
	QWidget::update();
}

void MainGame::clockCallback()
{
	if (status == PLAYING) { timeDuring += 1; }
}

void MainGame::setInterval()
{
    timer.interval.setInterval(1000 / GAME_FPS);
    timer.clock.setInterval(CLOCK_INTERVAL);
}

void MainGame::connectTimer()
{
    connect(&timer.interval, &QTimer::timeout, this, &MainGame::mainInterval);
    connect(&timer.clock, &QTimer::timeout, this, &MainGame::clockCallback);
}

void MainGame::connectAction()
{
    connect(ui->actionEasy, &QAction::triggered, this, &MainGame::setEasyLevel);
    connect(ui->actionNormal, &QAction::triggered, this, &MainGame::setNormalLevel);
    connect(ui->actionHigh, &QAction::triggered, this, &MainGame::setHighLevel);
    connect(ui->actionCustom, &QAction::triggered, this, &MainGame::setCustomLevel);
	connect(ui->actionPause, &QAction::triggered, this, &MainGame::setPause);
	connect(ui->actionRestart, &QAction::triggered, this, &MainGame::restart);
	connect(ui->actionRecord, &QAction::triggered, record, &RecordDialog::openDialog);
	connect(ui->actionAbout, &QAction::triggered, about, &AboutDialog::exec);
}

void MainGame::startTimer()
{
    timer.interval.start();
    timer.clock.start();
}

void MainGame::restart()
{
    audio.click.stop();
    audio.click.play();

    for (int i = 0; i < tableRows; i++)
    {
        for (int j = 0; j < tableCols; j++)
        {
			blocks[i][j].type = NONE;
			blocks[i][j].number = 0;
			blocks[i][j].isCovered = true;
			blocks[i][j].isMarked = false;
			blocks[i][j].isTouched = false;
			blocks[i][j].isError = false;
        }
    }
    status = PLAYING;
    flagCount = mineInitCount;
	timeDuring = 0;
    isCracked = false;
	isHaveCracked = false;
    addMine();
    addNumber();
}

void MainGame::initColor()
{
	color.white.setRgb(WHITE);
	color.black.setRgb(BLACK);
	color.gray.setRgb(GRAY);
}

void MainGame::addMine()
{
	static QVector <int> numbers;

	mines.clear();

	for (int i = 0; i < ROWS_MAX * COLS_MAX; i++)
	{
		numbers.append(i);
	}
	for (int i = 0; i < tableRows * tableCols; i++)
	{
		qSwap(numbers[i], numbers[rand() % (tableRows * tableCols)]);
	}
	for (int i = 0; i < mineInitCount; i++)
	{
		static QPoint temp;

		temp.setX(numbers[i] % tableRows);
		temp.setY(numbers[i] / tableRows);

		blocks[temp.x()][temp.y()].type = MINE;
		mines.append(temp);
	}
	numbers.clear();
}

void MainGame::addNumber()
{
    for (int i = 0; i < mineInitCount; i++)
    {
        for (int sideX = -1; sideX <= 1; sideX++)
        {
            for (int sideY = -1; sideY <= 1; sideY++)
            {
				int x = mines[i].x() + sideX;
				int y = mines[i].y() + sideY;

				if (x >= 0 && x < tableRows && y >= 0 && y < tableCols && blocks[x][y].type != MINE)
                {
					blocks[x][y].type = NUMBER;
					blocks[x][y].number += 1;
                }
            }
        }
    }
}

void MainGame::setRecord()
{
	record->getRecord(success->getInputName(), timeDuring, level);
}

void MainGame::setPause()
{
    if (status == PLAYING && !isCracked)
    {
        status = PAUSE;
    }
}

void MainGame::gameoverWin()
{
    for (int x = 0; x < tableRows; x++)
    {
        for (int y = 0; y < tableCols; y++)
        {
			if (blocks[x][y].type != MINE && blocks[x][y].isCovered)
            {
				return;
            }
        }
    }
	audio.win.stop();
	audio.win.play();
	status = WIN;

	if (level != CUSTOM && !isHaveCracked)
	{
		success->openDialog();
		if (success->getIsNeedSave()) { setRecord(); }
	}
}

void MainGame::gameoverLose(int x, int y)
{
    audio.lose.stop();
    audio.lose.play();

    for (int x = 0; x < tableRows; x++)
    {
        for (int y = 0; y < tableCols; y++)
        {
			if (blocks[x][y].type == MINE && !blocks[x][y].isMarked)
            {
				blocks[x][y].isCovered = false;
            }
			else if (blocks[x][y].type != MINE && blocks[x][y].isMarked)
            {
				blocks[x][y].isError = true;
            }
        }
    }
	blocks[x][y].isTouched = true;
    status = OVER;
}

void MainGame::autoUncover()
{
	static QVector <QPoint> nones;

    for (int x = 0; x < tableRows; x++)
    {
        for (int y = 0; y < tableCols; y++)
        {
			if (blocks[x][y].type == NONE && !blocks[x][y].isCovered)
            {
				static QPoint temp;

				temp.setX(x);
				temp.setY(y);

				nones.append(temp);
            }
        }
    }
	for (int i = 0; i < nones.size(); i++)
    {
        for (int sideX = -1; sideX <= 1; sideX++)
        {
            for (int sideY = -1; sideY <= 1; sideY++)
            {
				int x = nones[i].x() + sideX;
				int y = nones[i].y() + sideY;

				if (x >= 0 && x < tableRows && y >= 0 && y < tableCols && !blocks[x][y].isMarked)
                {
					blocks[x][y].isCovered = false;
                }
            }
        }
    }
	nones.clear();
}

void MainGame::mousePressEvent(QMouseEvent* event)
{
    int clicked = event->button();

    if (clicked && !isCracked)
    {
        if (status == PLAYING)
        {
            mouse = event->pos();

			if (mouse.x() < MARGIN_X || mouse.x() > screenWidth - MARGIN_X) { return; }
			if (mouse.y() < MARGIN_Y || mouse.y() > screenHeight - MARGIN_X) { return; }

			int x = ((mouse.x() - MARGIN_X) / BLOCK_SIZE);
			int y = ((mouse.y() - MARGIN_Y) / BLOCK_SIZE);

			if (clicked == Qt::LeftButton && blocks[x][y].isCovered && !blocks[x][y].isMarked)
			{
				if (blocks[x][y].type != MINE)
				{
					audio.click.stop();
					audio.click.play();
				}
				else { gameoverLose(x, y); }

				blocks[x][y].isCovered = false;
			}
			else if (clicked == Qt::RightButton && blocks[x][y].isCovered)
			{
				audio.click.stop();
				audio.click.play();

				if (!blocks[x][y].isMarked)
				{
					blocks[x][y].isMarked = true;
					flagCount -= 1;
				}
				else if (blocks[x][y].isMarked)
				{
					blocks[x][y].isMarked = false;
					flagCount += 1;
				}
			}
        }
        else if (status == PAUSE)
        {
            audio.click.stop();
            audio.click.play();
            status = PLAYING;
        }
		else { restart(); }
    }
}

void MainGame::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z && status == PLAYING)
    {
        isCracked = true;
		isHaveCracked = true;
    }
	if (event->key() == Qt::Key_R) { restart(); }
	if (event->key() == Qt::Key_P) { setPause(); }
}

void MainGame::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z && status == PLAYING)
    {
        isCracked = false;
    }
}

void MainGame::displayBackground(QPainter& painter)
{
	static QRect rect;

	painter.fillRect(0, 0, screenWidth, screenHeight, QBrush(color.white));

	rect.setX(MARGIN_X - BORDER);
	rect.setY(MARGIN_Y - BORDER);
	rect.setWidth(tableWidth + 2 * BORDER);
	rect.setHeight(tableHeight + 2 * BORDER);

	painter.fillRect(rect, QBrush(color.black));

	rect.setX(MARGIN_X - BLOCK_BORDER);
	rect.setY(MARGIN_Y - BLOCK_BORDER);
	rect.setWidth(tableWidth + 2 * BLOCK_BORDER);
	rect.setHeight(tableHeight + 2 * BLOCK_BORDER);

	painter.fillRect(rect, QBrush(color.gray));
}

void MainGame::displayBlock(QPainter& painter)
{
	static QRect rect;

	for (int x = 0; x < tableRows; x++)
    {
		for (int y = 0; y < tableCols; y++)
        {
			rect.setX(MARGIN_X + x * BLOCK_SIZE);
			rect.setY(MARGIN_Y + y * BLOCK_SIZE);
			rect.setWidth(BLOCK_SIZE);
			rect.setHeight(BLOCK_SIZE);

			if (status == PAUSE)
			{
				painter.drawPixmap(rect, image.cover);
				continue;
			}
			if (blocks[x][y].isCovered && !isCracked)
            {
				painter.drawPixmap(rect, image.cover);

				if (blocks[x][y].isError)
                {
					painter.drawPixmap(rect, image.error);
                }
				else if (blocks[x][y].isMarked)
                {
					painter.drawPixmap(rect, image.flag);
                }
				continue;
            }
			painter.drawPixmap(rect, image.block);

			if (blocks[x][y].type == NUMBER)
			{
				painter.drawPixmap(rect, image.number[blocks[x][y].number - 1]);
			}
			else if (blocks[x][y].type == MINE)
			{
				painter.drawPixmap(rect, (blocks[x][y].isTouched) ? image.mineError : image.mine);
			}
        }
    }
}

void MainGame::displayInfo(QPainter& painter)
{
	static QString text;

	switch (status)
    {
		case PAUSE: text = QString("TIME: %1 (PAUSE)").arg(timeDuring); break;
		default: text = QString("TIME: %1").arg(timeDuring); break;
    }
	painter.drawText(MARGIN_X, INFO_TOP, text);

    switch (status)
	{
		case OVER: text = "BOOM!"; break;
		case WIN: text = "Success!"; break;
		default: text = QString("MINES: %1").arg(flagCount); break;
    }
	painter.drawText(screenWidth - INFO_WIDTH, INFO_TOP, text);
}

void MainGame::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
    displayBackground(painter);
    displayBlock(painter);
    displayInfo(painter);
}
