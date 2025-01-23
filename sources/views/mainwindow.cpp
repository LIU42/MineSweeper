#include "views/mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    gameFramework = new GameFramework();
    gameResources = new GameResources();

    frameTimer = new QTimer(this);
    clockTimer = new QTimer(this);

    aboutDialog = new AboutDialog(this);
    customDialog = new CustomDialog(this);
    rankDialog = new RankDialog(this);
    successDialog = new SuccessDialog(this);

    ui->setupUi(this);
    ui->sceneWidget->setGameFramework(gameFramework);
    ui->sceneWidget->setGameResources(gameResources);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gameFramework;
    delete gameResources;

    delete frameTimer;
    delete clockTimer;

    delete aboutDialog;
    delete customDialog;
    delete rankDialog;
    delete successDialog;
}

void MainWindow::initialize()
{
    setupTimers();
    setupActions();
    setLevel1();

    frameTimer->setInterval(TimerInterval::FRAME);
    frameTimer->start();

    clockTimer->setInterval(TimerInterval::CLOCK);
    clockTimer->start();
}

void MainWindow::setLevel1()
{
    gameFramework->setLevel1();
    resizeWindow();
    restartGame();
}

void MainWindow::setLevel2()
{
    gameFramework->setLevel2();
    resizeWindow();
    restartGame();
}

void MainWindow::setLevel3()
{
    gameFramework->setLevel3();
    resizeWindow();
    restartGame();
}

void MainWindow::setCustomLevel()
{
    if (customDialog->exec() == 0)
    {
        int rows = customDialog->getInputRows();
        int cols = customDialog->getInputCols();

        gameFramework->setCustomLevel(rows, cols, customDialog->getInputMineCount());
        resizeWindow();
        restartGame();
    }
}

void MainWindow::resizeWindow()
{
    int rows = gameFramework->getRows();
    int cols = gameFramework->getCols();

    fitnessW = rows * UnitProperties::SIZE + WindowProperties::MARGIN_X + WindowProperties::MARGIN_X;
    fitnessH = cols * UnitProperties::SIZE + WindowProperties::MARGIN_X + WindowProperties::MARGIN_Y;

    setFixedSize(fitnessW, fitnessH);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), QGuiApplication::primaryScreen()->geometry()));
}

void MainWindow::setupTimers()
{
    connect(frameTimer, &QTimer::timeout, this, [=]
    {
        updateInfo();

        if (gameFramework->getStatus() == GameStatus::PLAYING)
        {
            judgeSuccess();

            if (isMinimized())
            {
                gameFramework->pause();
            }
            gameFramework->uncoverEmptyUnits();
        }
        ui->sceneWidget->update();
    });

    connect(clockTimer, &QTimer::timeout, this, [=]
    {
        if (gameFramework->getStatus() == GameStatus::PLAYING)
        {
            elapseTime += 1;
        }
    });
}

void MainWindow::setupActions()
{
    connect(ui->actionLevel1, &QAction::triggered, this, [=]
    {
        setLevel1();
    });

    connect(ui->actionLevel2, &QAction::triggered, this, [=]
    {
        setLevel2();
    });

    connect(ui->actionLevel3, &QAction::triggered, this, [=]
    {
        setLevel3();
    });

    connect(ui->actionCustom, &QAction::triggered, this, [=]
    {
        setCustomLevel();
    });

    connect(ui->actionPause, &QAction::triggered, this, [=]
    {
        gameFramework->pause();
    });

    connect(ui->actionRestart, &QAction::triggered, this, [=]
    {
        restartGame();
    });

    connect(ui->actionRecord, &QAction::triggered, this, [=]
    {
        rankDialog->exec();
    });

    connect(ui->actionAbout, &QAction::triggered, this, [=]
    {
        aboutDialog->exec();
    });
}

void MainWindow::updateInfo()
{
    ui->timeValueLabel->setNum(elapseTime);

    if (gameFramework->getStatus() == GameStatus::PAUSE)
    {
        ui->pauseInfoLabel->show();
    }
    else
    {
        ui->pauseInfoLabel->hide();
    }
    ui->remainValueLabel->setNum(gameFramework->getRemainFlagCount());
}

void MainWindow::restartGame()
{
    elapseTime = 0;

    gameResources->getClickSound()->stop();
    gameResources->getClickSound()->play();

    gameFramework->restart();
    gameFramework->addMines();
    gameFramework->addNumbers();
}

void MainWindow::judgeSuccess()
{
    if (!gameFramework->isSuccess())
    {
        return;
    }
    gameResources->getSuccessSound()->stop();
    gameResources->getSuccessSound()->play();

    if (gameFramework->getLevel() == GameLevel::CUSTOM || gameFramework->isCracked())
    {
        return;
    }
    if (successDialog->exec() == 0)
    {
        rankDialog->addRecord(successDialog->getInputName(), QString::number(elapseTime), gameFramework->getLevel());
    }
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (!event->button() || gameFramework->isCracking())
    {
        return;
    }
    if (gameFramework->getStatus() == GameStatus::PLAYING)
    {
        QPoint mouse = event->pos();

        if (mouse.x() < WindowProperties::MARGIN_X || mouse.x() > fitnessW - WindowProperties::MARGIN_X)
        {
            return;
        }
        if (mouse.y() < WindowProperties::MARGIN_Y || mouse.y() > fitnessH - WindowProperties::MARGIN_X)
        {
            return;
        }
        int x = (mouse.x() - WindowProperties::MARGIN_X) / UnitProperties::SIZE;
        int y = (mouse.y() - WindowProperties::MARGIN_Y) / UnitProperties::SIZE;

        if (event->button() == Qt::LeftButton && gameFramework->leftButtonClick(x, y))
        {
            if (gameFramework->isFailure(x, y))
            {
                gameResources->getFailureSound()->stop();
                gameResources->getFailureSound()->play();
            }
            else
            {
                gameResources->getClickSound()->stop();
                gameResources->getClickSound()->play();
            }
        }
        else if (event->button() == Qt::RightButton && gameFramework->rightButtonClick(x, y))
        {
            gameResources->getClickSound()->stop();
            gameResources->getClickSound()->play();
        }
    }
    else if (gameFramework->getStatus() == GameStatus::PAUSE)
    {
        gameResources->getClickSound()->stop();
        gameResources->getClickSound()->play();
        gameFramework->resume();
    }
    else
    {
        restartGame();
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_P)
    {
        gameFramework->pause();
    }
    else if (event->key() == Qt::Key_R)
    {
        restartGame();
    }
    else if (event->key() == Qt::Key_Z && gameFramework->getStatus() == GameStatus::PLAYING)
    {
        gameFramework->setCrackStart();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Z && gameFramework->getStatus() == GameStatus::PLAYING)
    {
        gameFramework->setCrackEnd();
    }
}
