#include "minesweeper.h"
#include "ui_minesweeper.h"

MainGame::MainGame(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainGame), about(this), custom(this), success(this), record(this)
{
    ui->setupUi(this);
}

MainGame::~MainGame()
{
    delete ui;
}

void MainGame::loadImage()
{
    image.block.load(":/Images/block.png");
    image.cover.load(":/Images/cover.png");
    image.error.load(":/Images/error.png");
    image.mine.load(":/Images/mine.png");
    image.mineError.load(":/Images/mine_error.png");
    image.flag.load(":/Images/flag.png");

    static char path[INFO_MAX_LEN];

    for (int i = 0; i < NUMBER_COUNT; i++)
    {
        sprintf(path, ":/Images/number_%d.png", i + 1);
        image.number[i].load(path);
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
    level = EASY_LEVEL;
    tableRows = TABLE_ROWS_EASY;
    tableCols = TABLE_COLS_EASY;
    mineInitCount = MINE_INIT_COUNT_EASY;
    resizeWindow();
    initGame();
}

void MainGame::setNormalLevel()
{
    level = NORMAL_LEVEL;
    tableRows = TABLE_ROWS_NORMAL;
    tableCols = TABLE_COLS_NORMAL;
    mineInitCount = MINE_INIT_COUNT_NORMAL;
    resizeWindow();
    initGame();
}

void MainGame::setHighLevel()
{
    level = HIGH_LEVEL;
    tableRows = TABLE_ROWS_HIGH;
    tableCols = TABLE_COLS_HIGH;
    mineInitCount = MINE_INIT_COUNT_HIGH;
    resizeWindow();
    initGame();
}

void MainGame::setCustomLevel()
{
    custom.initDialog();

	if (custom.getIfNeedSet())
    {
        level = CUSTOM_LEVEL;
        tableRows = custom.getInputRows();
        tableCols = custom.getInputCols();
        mineInitCount = custom.getInputMineCount();
        resizeWindow();
        initGame();
    }
}

void MainGame::resizeWindow()
{
    tableWidth = tableRows * BLOCK_WIDTH;
    tableHeight = tableCols * BLOCK_WIDTH;
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
        MainGame::update();
    }
    QWidget::update();
}

void MainGame::clockCallback()
{
    if (status == PLAYING) { timeSec += 1; }
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
    connect(ui->actionPause, &QAction::triggered, this, &MainGame::setPauseStatus);
    connect(ui->actionRestart, &QAction::triggered, this, &MainGame::initGame);
    connect(ui->actionRecord, &QAction::triggered, &record, &RecordDialog::initDialog);
    connect(ui->actionAbout, &QAction::triggered, &about, &AboutDialog::exec);
}

void MainGame::startTimer()
{
    timer.interval.start();
    timer.clock.start();
}

void MainGame::initGame()
{
    audio.click.stop();
    audio.click.play();

    for (int i = 0; i < tableRows; i++)
    {
        for (int j = 0; j < tableCols; j++)
        {
			blockData[i][j].type = NULL;
			blockData[i][j].number = 0;
			blockData[i][j].isCovered = true;
			blockData[i][j].isMarked = false;
			blockData[i][j].isTouched = false;
			blockData[i][j].isError = false;
        }
    }
    status = PLAYING;
    flagCount = mineInitCount;
    timeSec = 0;
    isCracked = false;
    ifHaveCracked = false;
    addMine();
    addNumber();
}

void MainGame::initColor()
{
    color.white.setRgb(COLOR_WHITE);
    color.gray.setRgb(COLOR_GRAY);
    color.black.setRgb(COLOR_BLACK);
}

void MainGame::addMine()
{
	static QVector <int> numberList;

	mineList.clear();

	for (int i = 0; i < TABLE_ROWS_MAX * TABLE_COLS_MAX; i++)
	{
		numberList.append(i);
	}
	for (int i = 0; i < tableRows * tableCols; i++)
	{
		qSwap(numberList[i], numberList[rand() % (tableRows * tableCols)]);
	}
	for (int i = 0; i < mineInitCount; i++)
	{
		int x = numberList[i] % tableRows;
		int y = numberList[i] / tableRows;

		blockData[x][y].type = MINE;
		mineList.append({ x, y });
	}
	numberList.clear();
}

void MainGame::addNumber()
{
    for (int i = 0; i < mineInitCount; i++)
    {
        for (int sideX = -1; sideX <= 1; sideX++)
        {
            for (int sideY = -1; sideY <= 1; sideY++)
            {
                int x = mineList[i].x + sideX;
                int y = mineList[i].y + sideY;

				if (x >= 0 && x < tableRows && y >= 0 && y < tableCols && blockData[x][y].type != MINE)
                {
					blockData[x][y].type = NUMBER;
					blockData[x][y].number += 1;
                }
            }
        }
    }
}

void MainGame::setRecord()
{
    switch (level)
    {
        case EASY_LEVEL: record.getRecord(success.getInputName(), timeSec, EASY_LEVEL); break;
        case HIGH_LEVEL: record.getRecord(success.getInputName(), timeSec, HIGH_LEVEL); break;
		case NORMAL_LEVEL: record.getRecord(success.getInputName(), timeSec, NORMAL_LEVEL); break;
    }
}

void MainGame::setPauseStatus()
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
			if (blockData[x][y].type != MINE && blockData[x][y].isCovered)
            {
				return;
            }
        }
    }
	audio.win.stop();
	audio.win.play();
	status = WIN;

	if (level != CUSTOM_LEVEL && !ifHaveCracked)
	{
		success.initDialog();
		if (success.getIfNeedSave()) { setRecord(); }
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
			if (blockData[x][y].type == MINE && !blockData[x][y].isMarked)
            {
				blockData[x][y].isCovered = false;
            }
			else if (blockData[x][y].type != MINE && blockData[x][y].isMarked)
            {
				blockData[x][y].isError = true;
            }
        }
    }
	blockData[x][y].isTouched = true;
    status = OVER;
}

void MainGame::update()
{
	static QVector <Point> nullList;

    for (int x = 0; x < tableRows; x++)
    {
        for (int y = 0; y < tableCols; y++)
        {
			if (blockData[x][y].type == NULL && !blockData[x][y].isCovered)
            {
				nullList.append({ x, y });
            }
        }
    }
	for (int i = 0; i < nullList.size(); i++)
    {
        for (int sideX = -1; sideX <= 1; sideX++)
        {
            for (int sideY = -1; sideY <= 1; sideY++)
            {
				int x = nullList[i].x + sideX;
				int y = nullList[i].y + sideY;

				if (x >= 0 && x < tableRows && y >= 0 && y < tableCols && !blockData[x][y].isMarked)
                {
					blockData[x][y].isCovered = false;
                }
            }
        }
    }
	nullList.clear();
}

void MainGame::mousePressEvent(QMouseEvent* event)
{
    int clicked = event->button();

    if (clicked && !isCracked)
    {
        if (status == PLAYING)
        {
            mouse = event->pos();

            if (mouse.x() >= MARGIN_X && mouse.x() <= screenWidth - MARGIN_X && mouse.y() >= MARGIN_Y && mouse.y() <= screenHeight - MARGIN_X)
            {
                int x = ((mouse.x() - MARGIN_X) / BLOCK_WIDTH);
                int y = ((mouse.y() - MARGIN_Y) / BLOCK_WIDTH);

				if (clicked == Qt::LeftButton && blockData[x][y].isCovered && !blockData[x][y].isMarked)
                {
					if (blockData[x][y].type != MINE)
                    {
                        audio.click.stop();
                        audio.click.play();
                    }
                    else { gameoverLose(x, y); }

					blockData[x][y].isCovered = false;
                }
				else if (clicked == Qt::RightButton && blockData[x][y].isCovered)
                {
                    audio.click.stop();
                    audio.click.play();

					if (!blockData[x][y].isMarked)
                    {
						blockData[x][y].isMarked = true;
                        flagCount -= 1;
                    }
					else if (blockData[x][y].isMarked)
                    {
						blockData[x][y].isMarked = false;
                        flagCount += 1;
                    }
                }
            }
        }
        else if (status == PAUSE)
        {
            audio.click.stop();
            audio.click.play();
            status = PLAYING;
        }
        else { initGame(); }
    }
}

void MainGame::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z && status == PLAYING)
    {
        isCracked = true;
        ifHaveCracked = true;
    }
    if (event->key() == Qt::Key_R) { initGame(); }
    if (event->key() == Qt::Key_P) { setPauseStatus(); }
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
    for (int i = 0; i < tableRows; i++)
    {
        for (int j = 0; j < tableCols; j++)
        {
            int x = MARGIN_X + i * BLOCK_WIDTH;
            int y = MARGIN_Y + j * BLOCK_WIDTH;

			if ((blockData[i][j].isCovered && !isCracked) || status == PAUSE)
            {
                painter.drawPixmap(x, y, BLOCK_WIDTH, BLOCK_WIDTH, image.cover);

				if (blockData[i][j].isError && status != PAUSE)
                {
                    painter.drawPixmap(x, y, BLOCK_WIDTH, BLOCK_WIDTH, image.error);
                }
				else if (blockData[i][j].isMarked && status != PAUSE)
                {
                    painter.drawPixmap(x, y, BLOCK_WIDTH, BLOCK_WIDTH, image.flag);
                }
            }
            else
            {
                painter.drawPixmap(x, y, BLOCK_WIDTH, BLOCK_WIDTH, image.block);

				if (blockData[i][j].type == NUMBER)
				{
					painter.drawPixmap(x, y, BLOCK_WIDTH, BLOCK_WIDTH, image.number[blockData[i][j].number - 1]);
				}
				else if (blockData[i][j].type == MINE)
				{
					painter.drawPixmap(x, y, BLOCK_WIDTH, BLOCK_WIDTH, (blockData[i][j].isTouched) ? image.mineError : image.mine);
				}
            }
        }
    }
}

void MainGame::displayInfo(QPainter& painter)
{
    static char text[INFO_MAX_LEN];

    switch (status)
    {
        case PAUSE: snprintf(text, INFO_MAX_LEN, "TIME: %d (PAUSE)", timeSec); break;
        default: snprintf(text, INFO_MAX_LEN, "TIME: %d", timeSec); break;
    }
	painter.drawText(MARGIN_X, INFO_POSITION_TOP, text);

    switch (status)
    {
        case OVER: snprintf(text, INFO_MAX_LEN, "BOOM!"); break;
        case WIN: snprintf(text, INFO_MAX_LEN, "Success!"); break;
        default: snprintf(text, INFO_MAX_LEN, "MINES: %d", flagCount); break;
    }
	painter.drawText(screenWidth - INFO_WIDTH, INFO_POSITION_TOP, text);
}

void MainGame::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    displayBackground(painter);
    displayBlock(painter);
    displayInfo(painter);
}
