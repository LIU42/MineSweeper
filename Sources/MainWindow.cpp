#include "MainWindow.h"
#include "ui_MainWindow.h"

GameTimers::GameTimers()
{
    pFrameTimer = new QTimer();
    pFrameTimer->setInterval(FRAME_INTERVAL);
    pFrameTimer->start();

    pClockTimer = new QTimer();
    pClockTimer->setInterval(CLOCK_INTERVAL);
    pClockTimer->start();
}

GameTimers::~GameTimers()
{
    delete pFrameTimer;
    delete pClockTimer;
}

GameAudio::GameAudio()
{
    pClickSound = new QSoundEffect();
    pSuccessSound = new QSoundEffect();
    pFailureSound = new QSoundEffect();

    pClickSound->setSource(QUrl("qrc:/Audio/click.wav"));
    pFailureSound->setSource(QUrl("qrc:/Audio/failure.wav"));
    pSuccessSound->setSource(QUrl("qrc:/Audio/success.wav"));
}

GameAudio::~GameAudio()
{
    delete pClickSound;
    delete pSuccessSound;
    delete pFailureSound;
}

GameDialogs::GameDialogs(QWidget* parent)
{
    pAboutDialog = new AboutDialog(parent);
    pCustomDialog = new CustomDialog(parent);
    pRecordDialog = new RecordDialog(parent);
    pSuccessDialog = new SuccessDialog(parent);
}

GameDialogs::~GameDialogs()
{
    delete pAboutDialog;
    delete pCustomDialog;
    delete pRecordDialog;
    delete pSuccessDialog;
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    pMainGame = new MainGame();
    pTimers = new GameTimers();
    pAudio = new GameAudio();
    pDialogs = new GameDialogs(this);

    ui->setupUi(this);
    ui->pGraphicsWidget->setMainGame(pMainGame);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pMainGame;
    delete pTimers;
    delete pAudio;
    delete pDialogs;
}

void MainWindow::init()
{
    connectTimer();
    connectAction();
    setGameEasyLevel();
}

void MainWindow::setGameEasyLevel()
{
    pMainGame->setEasyLevel();
    resizeWindow();
    restartGame();
}

void MainWindow::setGameNormalLevel()
{
    pMainGame->setNormalLevel();
    resizeWindow();
    restartGame();
}

void MainWindow::setGameHighLevel()
{
    pMainGame->setHighLevel();
    resizeWindow();
    restartGame();
}

void MainWindow::setGameCustomLevel()
{
    pDialogs->pCustomDialog->showDialog();

    if (pDialogs->pCustomDialog->getIsNeedSet())
    {
        int tableRows = pDialogs->pCustomDialog->getInputRows();
        int tableCols = pDialogs->pCustomDialog->getInputCols();
        int mineInitCount = pDialogs->pCustomDialog->getInputMineCount();

        pMainGame->setCustomLevel(tableRows, tableCols, mineInitCount);
        resizeWindow();
        restartGame();
    }
}

void MainWindow::resizeWindow()
{
    screenWidth = pMainGame->getTableRows() * GameBlock::SIZE + MARGIN_X + MARGIN_X;
    screenHeight = pMainGame->getTableCols() * GameBlock::SIZE + MARGIN_X + MARGIN_Y;

    setFixedSize(screenWidth, screenHeight);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), QGuiApplication::primaryScreen()->geometry()));
}

void MainWindow::mainInterval()
{
    updateGameInfo();
    
    if (pMainGame->getStatus() == GameStatus::STATUS_MAINLOOP)
    {
        gameoverSuccess();
        pauseIfMinimized();
        uncoverEmptyBlocks();
    }
    ui->pGraphicsWidget->update();
}

void MainWindow::clockCallback()
{
    if (pMainGame->getStatus() == GameStatus::STATUS_MAINLOOP)
    {
        elapseTime += 1;
    }
}

void MainWindow::connectTimer()
{
    connect(pTimers->pFrameTimer, &QTimer::timeout, this, &MainWindow::mainInterval);
    connect(pTimers->pClockTimer, &QTimer::timeout, this, &MainWindow::clockCallback);
}

void MainWindow::connectAction()
{
    connect(ui->pActionEasyLevel, &QAction::triggered, this, &MainWindow::setGameEasyLevel);
    connect(ui->pActionNormalLevel, &QAction::triggered, this, &MainWindow::setGameNormalLevel);
    connect(ui->pActionHighLevel, &QAction::triggered, this, &MainWindow::setGameHighLevel);
    connect(ui->pActionCustomLevel, &QAction::triggered, this, &MainWindow::setGameCustomLevel);
    connect(ui->pActionPause, &QAction::triggered, this, &MainWindow::pauseGame);
    connect(ui->pActionRestart, &QAction::triggered, this, &MainWindow::restartGame);
    connect(ui->pActionRecord, &QAction::triggered, pDialogs->pRecordDialog, &RecordDialog::showDialog);
    connect(ui->pActionAbout, &QAction::triggered, pDialogs->pAboutDialog, &AboutDialog::exec);
}

void MainWindow::updateGameInfo()
{
    QString timeInfo = QString("TIME: %1").arg(elapseTime);
    QString mineInfo = QString("MINES: %1").arg(pMainGame->getRemainFlagCount());

    if (pMainGame->getStatus() == GameStatus::STATUS_PAUSE)
    {
        timeInfo.append(" (PAUSE)");
    }
    if (pMainGame->getStatus() == GameStatus::STATUS_FAILURE)
    {
        mineInfo = "BOOM!";
    }
    if (pMainGame->getStatus() == GameStatus::STATUS_SUCCESS)
    {
        mineInfo = "Success!";
    }
    ui->pTimeLabel->setText(timeInfo);
    ui->pMineLabel->setText(mineInfo);
}

void MainWindow::restartGame()
{
    pAudio->pClickSound->stop();
    pAudio->pClickSound->play();

    pMainGame->restart();
    pMainGame->addMines();
    pMainGame->addNumbers();
    elapseTime = 0;
}

void MainWindow::pauseGame()
{
    pMainGame->setPause();
}

void MainWindow::gameoverSuccess()
{
    if (!pMainGame->isSuccess())
    {
        return;
    }
    pAudio->pSuccessSound->stop();
    pAudio->pSuccessSound->play();

    if (pMainGame->getLevel() == GameLevel::LEVEL_CUSTOM || pMainGame->getIsHaveCracked())
    {
        return;
    }
    pDialogs->pSuccessDialog->showDialog();

    if (pDialogs->pSuccessDialog->getIsNeedSave())
    {
        pDialogs->pRecordDialog->addRecord(pDialogs->pSuccessDialog->getInputName(), elapseTime, (int)pMainGame->getLevel());
    }
}

void MainWindow::pauseIfMinimized()
{
    if (isMinimized())
    {
        pauseGame();
    }
}

void MainWindow::uncoverEmptyBlocks()
{
    pMainGame->uncoverEmptyBlocks();
}

void MainWindow::mousePressEvent(QMouseEvent* pMouseEvent)
{
    if (!pMouseEvent->button() || pMainGame->getIsCracked())
    {
        return;
    }
    if (pMainGame->getStatus() == GameStatus::STATUS_MAINLOOP)
    {
        QPoint mouse = pMouseEvent->pos();

        if (mouse.x() < MARGIN_X || mouse.x() > screenWidth - MARGIN_X)
        {
            return;
        }
        if (mouse.y() < MARGIN_Y || mouse.y() > screenHeight - MARGIN_X)
        {
            return;
        }
        int x = ((mouse.x() - MARGIN_X) / GameBlock::SIZE);
        int y = ((mouse.y() - MARGIN_Y) / GameBlock::SIZE);

        if (pMouseEvent->button() == Qt::LeftButton && pMainGame->isLeftButtonClick(x, y))
        {
            if (pMainGame->isFailure(x, y))
            {
                pAudio->pFailureSound->stop();
                pAudio->pFailureSound->play();
            }
            else
            {
                pAudio->pClickSound->stop();
                pAudio->pClickSound->play();
            }
        }
        else if (pMouseEvent->button() == Qt::RightButton && pMainGame->isRightButtonClick(x, y))
        {
            pAudio->pClickSound->stop();
            pAudio->pClickSound->play();
        }
    }
    else if (pMainGame->getStatus() == GameStatus::STATUS_PAUSE)
    {
        pAudio->pClickSound->stop();
        pAudio->pClickSound->play();
        pMainGame->setResume();
    }
    else
    {
        restartGame();
    }
}

void MainWindow::keyPressEvent(QKeyEvent* pKeyEvent)
{
    if (pKeyEvent->key() == Qt::Key_Z && pMainGame->getStatus() == GameStatus::STATUS_MAINLOOP)
    {
        pMainGame->setCrackStart();
    }
    switch (pKeyEvent->key())
    {
        case Qt::Key_R: restartGame(); break;
        case Qt::Key_P: pauseGame(); break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* pKeyEvent)
{
    if (pKeyEvent->key() == Qt::Key_Z && pMainGame->getStatus() == GameStatus::STATUS_MAINLOOP)
    {
        pMainGame->setCrackEnd();
    }
}
