#include "../header/mainmenu.h"

MainMenu::MainMenu(QObject* parent):
    QGraphicsScene(parent)
{
    setSceneRect(0, 0, 1000, 600);
    srand(time(NULL));
    // curState = 0
    gameTitle = new QGraphicsTextItem("Chess Game");
    gameTitle->setFont(QFont("Arial", 70, QFont::Bold));
    gameTitle->setDefaultTextColor(Qt::white);
    gameTitle->setPos(1000/2.0 - gameTitle->boundingRect().width() / 2, 345/2.0 - gameTitle->boundingRect().height()/2);
    addItem(gameTitle);
    gameTitle->hide();
    btnPlayGame = new ButtonGame("Play Game", QRect(0, 0, 150, 40));
    btnLoadGame = new ButtonGame("Load Game", QRect(0, 0, 150, 40));
    btnThemes = new ButtonGame("Themes", QRect(0, 0, 150, 40));
    btnSettings = new ButtonGame("Settings", QRect(0, 0, 150, 40));
    btnExit = new ButtonGame("Exit Game", QRect(0, 0, 150, 40));
    btnPlayGame->setPos(425, 345);
    btnLoadGame->setPos(425, 385);
    btnThemes->setPos(425, 425);
    btnSettings->setPos(425, 465);
    btnExit->setPos(425, 505);
    btnsState[0].push_back(btnPlayGame);
    btnsState[0].push_back(btnLoadGame);
    btnsState[0].push_back(btnThemes);
    btnsState[0].push_back(btnSettings);
    btnsState[0].push_back(btnExit);
    addItem(btnPlayGame);
    addItem(btnLoadGame);
    addItem(btnThemes);
    addItem(btnSettings);
    addItem(btnExit);
    connect(btnPlayGame, &ButtonGame::clicked, this, &MainMenu::onPlayGameClicked);
    connect(btnLoadGame, &ButtonGame::clicked, this, [&]() {
        emit loadgameActivated();
    });
    connect(btnThemes, &ButtonGame::clicked, this, [&]() {
        emit themeActivated();
    });
    connect(btnSettings, &ButtonGame::clicked, this, [&]() {
        emit settingsActivated();
    });
    connect(btnExit, &ButtonGame::clicked, this, [&]() {
        emit exitActivated();
    });

    //	curState = 1
    txtGameMode = new QGraphicsTextItem("Chosse game Mode");
    txtGameMode->setFont(QFont("Arial", 30, QFont::Bold));
    txtGameMode->setDefaultTextColor(Qt::white);
    txtGameMode->setPos(1000/2.0 - txtGameMode->boundingRect().width() / 2, 345/2.0 - txtGameMode->boundingRect().height() / 2);
    addItem(txtGameMode);
    txtGameMode->hide();
    btnPvP = new ButtonGame("PvP", QRect(0, 0, 150, 40));
    btnPvE = new ButtonGame("PvE", QRect(0, 0, 150, 40));
    btnBack = new ButtonGame("Back", QRect(0, 0, 150, 40));
    btnPvP->setPos(425, 345);
    btnPvE->setPos(425, 385);
    btnsState[1].push_back(btnPvP);
    btnsState[1].push_back(btnPvE);
    btnsState[1].push_back(btnBack);
    addItem(btnPvP);
    addItem(btnPvE);
    addItem(btnBack);
    connect(btnPvP, &ButtonGame::clicked, this, [&]() {
        gameMode = 0;
        playerSide = 1;
        gameDifficulty = 0;
        emit playgameActivated();
    });
    connect(btnPvE, &ButtonGame::clicked, this, &MainMenu::onPvEClicked);

    // curState = 2
    txtGameDifficulty = new QGraphicsTextItem("Chosse game Difficulty");
    txtGameDifficulty->setFont(QFont("Arial", 30, QFont::Bold));
    txtGameDifficulty->setDefaultTextColor(Qt::white);
    txtGameDifficulty->setPos(1000/2.0 - txtGameDifficulty->boundingRect().width() / 2, 345/2.0 - txtGameDifficulty->boundingRect().height() / 2);
    addItem(txtGameDifficulty);
    txtGameDifficulty->hide();
    btnEasy = new ButtonGame("Easy", QRect(0, 0, 150, 40));
    btnMedium = new ButtonGame("Medium", QRect(0, 0, 150, 40));
    btnHard = new ButtonGame("Hard", QRect(0, 0, 150, 40));
    btnEasy->setPos(425, 345);
    btnMedium->setPos(425, 385);
    btnHard->setPos(425, 425);
    btnsState[2].push_back(btnEasy);
    btnsState[2].push_back(btnMedium);
    btnsState[2].push_back(btnHard);
    btnsState[2].push_back(btnBack);
    addItem(btnEasy);
    addItem(btnMedium);
    addItem(btnHard);
    connect(btnEasy, &ButtonGame::clicked, this, [&]() {
        gameMode = 1;
        gameDifficulty = 0;
        preState = 2;
        hideState(preState);
        curState = 3;
        setupState(curState);
    });
    connect(btnMedium, &ButtonGame::clicked, this, [&]() {
        gameMode = 1;
        gameDifficulty = 1;
        preState = 2;
        hideState(preState);
        curState = 3;
        setupState(curState);
    });
    connect(btnHard, &ButtonGame::clicked, this, [&]() {
        gameMode = 1;
        gameDifficulty = 2;
        preState = 2;
        hideState(preState);
        curState = 3;
        setupState(curState);
    });

    connect(btnBack, &ButtonGame::clicked, this, &MainMenu::onBackClicked);

    for (int i = 1; i <= 2; ++i) {
        for (auto btn : btnsState[i]) {
            btn->hide();
        }
    }

    gameModeFlicker = new QTimer(this);
    gameDifficultyFlicker = new QTimer(this);
    connect(gameModeFlicker, &QTimer::timeout, this, [&]() {
        txtGameMode->setVisible(!txtGameMode->isVisible());
    });
    connect(gameDifficultyFlicker, &QTimer::timeout, this, [&]() {
        txtGameDifficulty->setVisible(!txtGameDifficulty->isVisible());
    });

    // curState = 3
    txtPlayerSide = new QGraphicsTextItem("Chosse your side");
    txtPlayerSide->setFont(QFont("Arial", 30, QFont::Bold));
    txtPlayerSide->setDefaultTextColor(Qt::white);
    txtPlayerSide->setPos((1000 - txtPlayerSide->boundingRect().width())/2, 120);
    playerSideFlicker = new QTimer(this);
    connect(playerSideFlicker, &QTimer::timeout, this, [&]() {
        txtPlayerSide->setVisible(!txtPlayerSide->isVisible());
    });

    btnWhiteSide = new SvgButton(":/assets/buttons/whiteside.svg");
    btnBlackSide = new SvgButton(":/assets/buttons/blackside.svg");
    btnRandomSide = new SvgButton(":/assets/buttons/randomside.svg");
    btnWhiteSide->fixSize(150);
    btnBlackSide->fixSize(150);
    btnRandomSide->fixSize(150);
    btnWhiteSide->setPos(225, 270);
    btnBlackSide->setPos(425, 270);
    btnRandomSide->setPos(625, 270);
    addItem(txtPlayerSide);   txtPlayerSide->hide();
    addItem(btnWhiteSide);    btnWhiteSide->hide();
    addItem(btnBlackSide);    btnBlackSide->hide();
    addItem(btnRandomSide);   btnRandomSide->hide();

    connect(btnWhiteSide, &SvgButton::clicked, this, [&]() {
        playerSide = 1;
        emit playgameActivated();
    });
    connect(btnBlackSide, &SvgButton::clicked, this, [&]() {
        playerSide = 0;
        emit playgameActivated();
    });
    connect(btnRandomSide, &SvgButton::clicked, this, [&]() {
        playerSide = rand() % 2;
        emit playgameActivated();
    });

    //btnWhiteSide->show();
    //btnWhiteSide->setPos(0, 0);

    btnBackPreScene = new SvgButton(":/assets/buttons/back.svg");
    btnBackPreScene->fixSize(50);
    btnBackPreScene->setPos(10, 10);
    addItem(btnBackPreScene); btnBackPreScene->hide();
    connect(btnBackPreScene, &SvgButton::clicked, this, [&]() {
        emit backActivated();
    });

    btnMainMenu = new ButtonGame("Main Menu", QRect(0, 0, 150, 40));
    addItem(btnMainMenu); btnMainMenu->hide();
    connect(btnMainMenu, &ButtonGame::clicked, this, [&](){
        hideAllButtons();
        btnPlayGame->setPos(425, 345);
        btnLoadGame->setPos(425, 385);
        btnThemes->setPos(425, 425);
        btnSettings->setPos(425, 465);
        btnExit->setPos(425, 505);
        curState = 0;
        setupState(curState);
        emit mainMenuActivated();
    });

    setupState(0);
}

void MainMenu::setupState(int state) {
    switch (state){
        case 0:
            sceneNum = 0;
            gameTitle->show();
            for (auto btn : btnsState[0]) {
                btn->show();
            }
            break;
        case 1:
            txtGameMode->show();
            gameModeFlicker->start(500);
            for (auto btn : btnsState[1]) {
                btn->show();
            }
            btnBack->setPos(425, 425);
            break;
        case 2:
            txtGameDifficulty->show();
            gameDifficultyFlicker->start(500);
            for (auto btn : btnsState[2]) {
                btn->show();
            }
            btnBack->setPos(425, 465);
            break;
        case 3:
            txtPlayerSide->show();
            playerSideFlicker->start(500);
            btnWhiteSide->show();
            btnBlackSide->show();
            btnRandomSide->show();
            btnBack->show();
            btnBack->setPos(425, 500);
            break;
        case 4:              // new game
            btnThemes->show();
            btnSettings->show();
            btnMainMenu->show();
            btnBack->show();
            btnThemes->setPos(425, 345);
            btnSettings->setPos(425, 385);
            btnMainMenu->setPos(425, 425);
            btnBack->setPos(425, 465);
            break;
    }
}

void MainMenu::hideState(int state) {
    switch (state) {
        case 0:
            btnBackPreScene->hide();
            gameTitle->hide();
            for (auto btn : btnsState[0]) {
                btn->hide();
            }
            break;
        case 1:
            btnBackPreScene->hide();
            txtGameMode->hide();
            gameModeFlicker->stop();
            for (auto btn : btnsState[1]) {
                btn->hide();
            }
            break;
        case 2:
            btnBackPreScene->hide();
            txtGameDifficulty->hide();
            gameDifficultyFlicker->stop();
            for (auto btn : btnsState[2]) {
                btn->hide();
            }
            break;
        case 3:
            btnBackPreScene->hide();
            txtPlayerSide->hide();
            playerSideFlicker->stop();
            btnWhiteSide->hide();
            btnBlackSide->hide();
            btnRandomSide->hide();
            btnBack->hide();
            break;
        case 4:              // new game
            btnThemes->hide();
            btnSettings->hide();
            btnMainMenu->hide();
            btnBack->hide();
            break;
    }
}

void MainMenu::onPlayGameClicked() {
    preState = 0;
    hideState(preState);
    curState = 1;
    setupState(curState);
}

void MainMenu::onPvEClicked() {
    preState = 1;
    hideState(preState);
    curState = 2;
    setupState(curState);
}

void MainMenu::onBackClicked() {
    if(sceneNum == 1 && (curState == 1 || curState == 4)){
        emit backActivated();
        return;
    }
    hideState(curState);
    --curState;
    setupState(curState);
}

void MainMenu::hideAllButtons() {
    if (btnPlayGame->isVisible()) btnPlayGame->setVisible(false);
    if (btnLoadGame->isVisible()) btnLoadGame->setVisible(false);
    if (btnThemes->isVisible()) btnThemes->setVisible(false);
    if (btnSettings->isVisible()) btnSettings->setVisible(false);
    if (btnExit->isVisible()) btnExit->setVisible(false);
    if (btnPvP->isVisible()) btnPvP->setVisible(false);
    if (btnPvE->isVisible()) btnPvE->setVisible(false);
    if (btnEasy->isVisible()) btnEasy->setVisible(false);
    if (btnMedium->isVisible()) btnMedium->setVisible(false);
    if (btnHard->isVisible()) btnHard->setVisible(false);
    if (btnBack->isVisible()) btnBack->setVisible(false);
    if (btnWhiteSide->isVisible()) btnWhiteSide->setVisible(false);
    if (btnBlackSide->isVisible()) btnBlackSide->setVisible(false);
    if (btnRandomSide->isVisible()) btnRandomSide->setVisible(false);
    if (btnMainMenu->isVisible()) btnMainMenu->setVisible(false);

    if (gameTitle->isVisible()) gameTitle->setVisible(false);
    playerSideFlicker->stop();
    gameDifficultyFlicker->stop();
    gameModeFlicker->stop();
    if (txtGameDifficulty->isVisible()) txtGameDifficulty->setVisible(false);
    if (txtGameMode->isVisible()) txtGameMode->setVisible(false);
    if (txtPlayerSide->isVisible()) txtPlayerSide->setVisible(false);
}

MainMenu::~MainMenu() {
    // Delete dynamically allocated ButtonGame objects
    delete btnPlayGame;
    delete btnLoadGame;
    delete btnThemes;
    delete btnSettings;
    delete btnExit;
    delete btnPvP;
    delete btnPvE;
    delete btnEasy;
    delete btnMedium;
    delete btnHard;
    delete btnBack;
    delete btnMainMenu;

    // Delete any dynamically allocated SvgButtons
    delete btnWhiteSide;
    delete btnBlackSide;
    delete btnRandomSide;
    delete btnBackPreScene;

    // Delete any dynamically allocated QGraphicsTextItems
    delete gameTitle;
    delete txtGameMode;
    delete txtGameDifficulty;
    delete txtPlayerSide;

    // Delete dynamically allocated QTimers
    delete gameModeFlicker;
    delete gameDifficultyFlicker;
    delete playerSideFlicker;

    // Clear button states if necessary
    // for (auto& btnList : btnsState) {
    //     btnList.clear();
    // }
    // listBtn.clear();
}
