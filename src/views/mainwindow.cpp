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

    pGameEnvironment = new GameEnvironment();
    pGameResources = new GameResources();

    pAboutDialog = new AboutDialog(this);
    pCustomDialog = new CustomDialog(this);
    pRecordDialog = new RecordDialog(this);
    pSuccessDialog = new SuccessDialog(this);

    ui->setupUi(this);
    ui->pSceneWidget->setGameEnvironment(pGameEnvironment);
    ui->pSceneWidget->setGameResources(pGameResources);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pGameEnvironment;
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
    pGameEnvironment->setLevel1();
    resizeWindow();
    restart();
}

void MainWindow::setLevel2()
{
    pGameEnvironment->setLevel2();
    resizeWindow();
    restart();
}

void MainWindow::setLevel3()
{
    pGameEnvironment->setLevel3();
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

        pGameEnvironment->setCustomLevel(rows, cols, pCustomDialog->getInputMineCount());
        resizeWindow();
        restart();
    }
}

void MainWindow::resizeWindow()
{
    int rows = pGameEnvironment->getRows();
    int cols = pGameEnvironment->getCols();

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

        if (pGameEnvironment->getStatus() == GameStatus::PLAYING)
        {
            judgeSuccess();

            if (isMinimized())
            {
                pGameEnvironment->setPause();
            }
            pGameEnvironment->uncoverEmptyBlocks();
        }
        ui->pSceneWidget->update();
    });

    connect(pClockTimer, &QTimer::timeout, this, [=]
    {
        if (pGameEnvironment->getStatus() == GameStatus::PLAYING)
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
        pGameEnvironment->setPause();
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

    if (pGameEnvironment->getStatus() == GameStatus::PAUSE)
    {
        ui->pTimeLabel->setText(ui->pTimeLabel->text().append(" (PAUSE)"));
    }
    if (pGameEnvironment->getStatus() == GameStatus::FAILURE)
    {
        ui->pMineLabel->setText("BOOM!");
    }
    else if (pGameEnvironment->getStatus() == GameStatus::SUCCESS)
    {
        ui->pMineLabel->setText("Success!");
    }
    else
    {
        ui->pMineLabel->setText(QString("MINES: %1").arg(pGameEnvironment->getRemainFlagCount()));
    }
}

void MainWindow::restart()
{
    elapseTime = 0;

    pGameResources->getClickSound()->stop();
    pGameResources->getClickSound()->play();

    pGameEnvironment->restart();
    pGameEnvironment->addMines();
    pGameEnvironment->addNumbers();
}

void MainWindow::judgeSuccess()
{
    if (!pGameEnvironment->isSuccess())
    {
        return;
    }
    pGameResources->getSuccessSound()->stop();
    pGameResources->getSuccessSound()->play();

    if (pGameEnvironment->getLevel() == GameLevel::CUSTOM || pGameEnvironment->isCracked())
    {
        return;
    }
    pSuccessDialog->show();

    if (pSuccessDialog->isNeedSave())
    {
        pRecordDialog->addRecord(pSuccessDialog->getInputName(), elapseTime, pGameEnvironment->getLevel());
    }
}

void MainWindow::mousePressEvent(QMouseEvent* pMouseEvent)
{
    if (!pMouseEvent->button() || pGameEnvironment->isCracking())
    {
        return;
    }
    if (pGameEnvironment->getStatus() == GameStatus::PLAYING)
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

        if (pMouseEvent->button() == Qt::LeftButton && pGameEnvironment->leftButtonClick(x, y))
        {
            if (pGameEnvironment->isFailure(x, y))
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
        else if (pMouseEvent->button() == Qt::RightButton && pGameEnvironment->rightButtonClick(x, y))
        {
            pGameResources->getClickSound()->stop();
            pGameResources->getClickSound()->play();
        }
    }
    else if (pGameEnvironment->getStatus() == GameStatus::PAUSE)
    {
        pGameResources->getClickSound()->stop();
        pGameResources->getClickSound()->play();
        pGameEnvironment->setResume();
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
        pGameEnvironment->setPause();
    }
    else if (pKeyEvent->key() == Qt::Key_R)
    {
        restart();
    }
    else if (pKeyEvent->key() == Qt::Key_Z && pGameEnvironment->getStatus() == GameStatus::PLAYING)
    {
        pGameEnvironment->setCrackStart();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* pKeyEvent)
{
    if (pKeyEvent->key() == Qt::Key_Z && pGameEnvironment->getStatus() == GameStatus::PLAYING)
    {
        pGameEnvironment->setCrackEnd();
    }
}
