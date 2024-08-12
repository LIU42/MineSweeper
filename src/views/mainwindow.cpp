#include "views/mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    pFrameTimer = new QTimer();
    pFrameTimer->setInterval(WindowProperties::FRAME_INTERVAL);
    pFrameTimer->start();

    pClockTimer = new QTimer();
    pClockTimer->setInterval(WindowProperties::CLOCK_INTERVAL);
    pClockTimer->start();

    pGameController = new GameController();
    pGameResources = new GameResources();

    pAboutDialog = new AboutDialog(this);
    pCustomDialog = new CustomDialog(this);
    pRecordDialog = new RecordDialog(this);
    pSuccessDialog = new SuccessDialog(this);

    ui->setupUi(this);
    ui->pSceneWidget->setGameController(pGameController);
    ui->pSceneWidget->setGameResources(pGameResources);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pGameController;
    delete pGameResources;

    delete pFrameTimer;
    delete pClockTimer;

    delete pAboutDialog;
    delete pCustomDialog;
    delete pRecordDialog;
    delete pSuccessDialog;
}

void MainWindow::init()
{
    setupTimers();
    setupActions();
    setLevel1();
}

void MainWindow::setLevel1()
{
    pGameController->setLevel1();
    resizeWindow();
    restart();
}

void MainWindow::setLevel2()
{
    pGameController->setLevel2();
    resizeWindow();
    restart();
}

void MainWindow::setLevel3()
{
    pGameController->setLevel3();
    resizeWindow();
    restart();
}

void MainWindow::setCustomLevel()
{
    pCustomDialog->show();

    if (pCustomDialog->isNeedSet())
    {
        int rows = pCustomDialog->getInputRows();
        int cols = pCustomDialog->getInputCols();

        pGameController->setCustomLevel(rows, cols, pCustomDialog->getInputMineCount());
        resizeWindow();
        restart();
    }
}

void MainWindow::resizeWindow()
{
    int rows = pGameController->getRows();
    int cols = pGameController->getCols();

    windowWidth = rows * SceneProperties::BLOCK_SIZE + WindowProperties::MARGIN_X + WindowProperties::MARGIN_X;
    windowHeight = cols * SceneProperties::BLOCK_SIZE + WindowProperties::MARGIN_X + WindowProperties::MARGIN_Y;

    setFixedSize(windowWidth, windowHeight);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), QGuiApplication::primaryScreen()->geometry()));
}

void MainWindow::setupTimers()
{
    connect(pFrameTimer, &QTimer::timeout, this, [=]
    {
        updateInfo();

        if (pGameController->getStatus() == GameStatus::PLAYING)
        {
            judgeSuccess();

            if (isMinimized())
            {
                pGameController->setPause();
            }
            pGameController->uncoverEmptyBlocks();
        }
        ui->pSceneWidget->update();
    });

    connect(pClockTimer, &QTimer::timeout, this, [=]
    {
        if (pGameController->getStatus() == GameStatus::PLAYING)
        {
            elapseTime += 1;
        }
    });
}

void MainWindow::setupActions()
{
    connect(ui->pActionLevel1, &QAction::triggered, this, [=]
    {
        setLevel1();
    });

    connect(ui->pActionLevel2, &QAction::triggered, this, [=]
    {
        setLevel2();
    });

    connect(ui->pActionLevel3, &QAction::triggered, this, [=]
    {
        setLevel3();
    });

    connect(ui->pActionCustom, &QAction::triggered, this, [=]
    {
        setCustomLevel();
    });

    connect(ui->pActionPause, &QAction::triggered, this, [=]
    {
        pGameController->setPause();
    });

    connect(ui->pActionRestart, &QAction::triggered, this, [=]
    {
        restart();
    });

    connect(ui->pActionRecord, &QAction::triggered, this, [=]
    {
        pRecordDialog->show();
    });

    connect(ui->pActionAbout, &QAction::triggered, this, [=]
    {
        pAboutDialog->exec();
    });
}

void MainWindow::updateInfo()
{
    ui->pTimeLabel->setText(QString("TIME: %1").arg(elapseTime));

    if (pGameController->getStatus() == GameStatus::PAUSE)
    {
        ui->pTimeLabel->setText(ui->pTimeLabel->text().append(" (PAUSE)"));
    }
    if (pGameController->getStatus() == GameStatus::FAILURE)
    {
        ui->pMineLabel->setText("BOOM!");
    }
    else if (pGameController->getStatus() == GameStatus::SUCCESS)
    {
        ui->pMineLabel->setText("Success!");
    }
    else
    {
        ui->pMineLabel->setText(QString("MINES: %1").arg(pGameController->getRemainFlagCount()));
    }
}

void MainWindow::restart()
{
    elapseTime = 0;

    pGameResources->getClickSound()->stop();
    pGameResources->getClickSound()->play();

    pGameController->restart();
    pGameController->addMines();
    pGameController->addNumbers();
}

void MainWindow::judgeSuccess()
{
    if (!pGameController->isSuccess())
    {
        return;
    }
    pGameResources->getSuccessSound()->stop();
    pGameResources->getSuccessSound()->play();

    if (pGameController->getLevel() == GameLevel::CUSTOM || pGameController->isCracked())
    {
        return;
    }
    pSuccessDialog->show();

    if (pSuccessDialog->isNeedSave())
    {
        pRecordDialog->addRecord(pSuccessDialog->getInputName(), elapseTime, pGameController->getLevel());
    }
}

void MainWindow::mousePressEvent(QMouseEvent* pMouseEvent)
{
    if (!pMouseEvent->button() || pGameController->isCracking())
    {
        return;
    }
    if (pGameController->getStatus() == GameStatus::PLAYING)
    {
        QPoint mouse = pMouseEvent->pos();

        if (mouse.x() < WindowProperties::MARGIN_X || mouse.x() > windowWidth - WindowProperties::MARGIN_X)
        {
            return;
        }
        if (mouse.y() < WindowProperties::MARGIN_Y || mouse.y() > windowHeight - WindowProperties::MARGIN_X)
        {
            return;
        }
        int x = (mouse.x() - WindowProperties::MARGIN_X) / SceneProperties::BLOCK_SIZE;
        int y = (mouse.y() - WindowProperties::MARGIN_Y) / SceneProperties::BLOCK_SIZE;

        if (pMouseEvent->button() == Qt::LeftButton && pGameController->leftButtonClick(x, y))
        {
            if (pGameController->isFailure(x, y))
            {
                pGameResources->getFailureSound()->stop();
                pGameResources->getFailureSound()->play();
            }
            else
            {
                pGameResources->getClickSound()->stop();
                pGameResources->getClickSound()->play();
            }
        }
        else if (pMouseEvent->button() == Qt::RightButton && pGameController->rightButtonClick(x, y))
        {
            pGameResources->getClickSound()->stop();
            pGameResources->getClickSound()->play();
        }
    }
    else if (pGameController->getStatus() == GameStatus::PAUSE)
    {
        pGameResources->getClickSound()->stop();
        pGameResources->getClickSound()->play();
        pGameController->setResume();
    }
    else
    {
        restart();
    }
}

void MainWindow::keyPressEvent(QKeyEvent* pKeyEvent)
{
    if (pKeyEvent->key() == Qt::Key_P)
    {
        pGameController->setPause();
    }
    else if (pKeyEvent->key() == Qt::Key_R)
    {
        restart();
    }
    else if (pKeyEvent->key() == Qt::Key_Z && pGameController->getStatus() == GameStatus::PLAYING)
    {
        pGameController->setCrackStart();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* pKeyEvent)
{
    if (pKeyEvent->key() == Qt::Key_Z && pGameController->getStatus() == GameStatus::PLAYING)
    {
        pGameController->setCrackEnd();
    }
}
