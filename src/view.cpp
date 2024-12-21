#include "../header/view.h"

View::View() :
	m_chessBoard(new ChessBoard()),
	m_mainMenu(new MainMenu()),
	m_themesSetting(new ThemesSetting()),
    m_settingsMenu(new SettingsMenu()),
    m_loadGameUI(new LoadGameUI())
{
	setWindowTitle("Chess Game BL");
	setFixedSize(QSize(Width, Height));
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setStyleSheet(QString("QGraphicsView { border-image: url(%1) 0 0 0 0 stretch stretch; }").arg(":/assets/backgroundimage/chessgame_menu.jpg"));
	setScene(m_mainMenu);
    sceneNum = 0;

	// Main Menu
    connect(m_mainMenu, &MainMenu::playgameActivated, this, [&]() {
        setStyleSheet(QString("QGraphicsView { border-image: url(%1) 0 0 0 0 stretch stretch; }").arg(":/assets/backgroundimage/chessboard_background.jpg"));
		m_chessBoard->setGameMode(m_mainMenu->gameMode, m_mainMenu->gameDifficulty, m_mainMenu->playerSide);
		m_chessBoard->resetBoard();
        sceneNum = 1;
		setScene(m_chessBoard);
	});
    connect(m_mainMenu, &MainMenu::loadgameActivated, this, [&](){
        m_loadGameUI->reloadJsonFileList();
        setScene(m_loadGameUI);
    });
    connect(m_mainMenu, &MainMenu::themeActivated, this, [&]() {
		setScene(m_themesSetting);
	});
    connect(m_mainMenu, &MainMenu::mainMenuActivated, this, [&](){
        sceneNum = 0;
    });
    connect(m_mainMenu, &MainMenu::settingsActivated, this, [&]() {
		setScene(m_settingsMenu);
	});
    connect(m_mainMenu, &MainMenu::exitActivated, this, [&]() {
		close();
	});
    connect(m_mainMenu, &MainMenu::backActivated, this, [&](){
        if(sceneNum == 1){
            setStyleSheet(QString("QGraphicsView { border-image: url(%1) 0 0 0 0 stretch stretch; }").arg(":/assets/backgroundimage/chessboard_background.jpg"));
            setScene(m_chessBoard);
        }
    });

    // Load Game UI
    connect(m_loadGameUI, &LoadGameUI::playgameActivated, this, [&](const GameData& data){
        setStyleSheet(QString("QGraphicsView { border-image: url(%1) 0 0 0 0 stretch stretch; }").arg(":/assets/backgroundimage/chessboard_background.jpg"));
        m_chessBoard->loadGame(data);
        sceneNum = 1;
        setScene(m_chessBoard);
    });
    connect(m_loadGameUI, &LoadGameUI::backActivated, this, [&](){
        switch (sceneNum){
            case 0:
                setStyleSheet(QString("QGraphicsView { border-image: url(%1) 0 0 0 0 stretch stretch; }").arg(":/assets/backgroundimage/chessgame_menu.jpg"));
                setScene(m_mainMenu);
                break;
            case 1:
                setStyleSheet(QString("QGraphicsView { border-image: url(%1) 0 0 0 0 stretch stretch; }").arg(":/assets/backgroundimage/chessboard_background.jpg"));
                setScene(m_chessBoard);
                break;
        }
    });

	// Themes Setting
    connect(m_themesSetting, &ThemesSetting::backActivated, this, [&]() {
        if(sceneNum == 1){
            m_mainMenu->sceneNum = sceneNum;
            m_mainMenu->curState = 4;
            m_mainMenu->hideAllButtons();
            m_mainMenu->setupState(4);
        }
        setStyleSheet(QString("QGraphicsView { border-image: url(%1) 0 0 0 0 stretch stretch; }").arg(":/assets/backgroundimage/chessgame_menu.jpg"));
		setScene(m_mainMenu);
	});
    connect(m_themesSetting, &ThemesSetting::saveChangeActivated, this, [&]() {
        setStyleSheet(QString("QGraphicsView { border-image: url(%1) 0 0 0 0 stretch stretch; }").arg(":/assets/backgroundimage/chessgame_menu.jpg"));
		m_chessBoard->setTheme(m_themesSetting->tilesTheme, m_themesSetting->piecesTheme);
	});

	// Settings Menu
    connect(m_settingsMenu, &SettingsMenu::backActivated, this, [&]() {
        if(sceneNum == 1){
            m_mainMenu->sceneNum = sceneNum;
            m_mainMenu->curState = 4;
            m_mainMenu->hideAllButtons();
            m_mainMenu->setupState(4);
        }
        setStyleSheet(QString("QGraphicsView { border-image: url(%1) 0 0 0 0 stretch stretch; }").arg(":/assets/backgroundimage/chessgame_menu.jpg"));
        setScene(m_mainMenu);
	});
    connect(m_settingsMenu, &SettingsMenu::soundEffectVolumeChanged, this, [&](){
        m_chessBoard->soundEffect.resetVolume(m_settingsMenu->soundEffectVolume);
    });

	// ChessBoard
    connect(m_chessBoard, &ChessBoard::menuActivated, this, [&]() {
        m_mainMenu->sceneNum = sceneNum;
        m_mainMenu->curState = 4;
        m_mainMenu->hideAllButtons();
        m_mainMenu->setupState(4);
        setStyleSheet(QString("QGraphicsView { border-image: url(%1) 0 0 0 0 stretch stretch; }").arg(":/assets/backgroundimage/chessgame_menu.jpg"));
		setScene(m_mainMenu);
	});
    connect(m_chessBoard, &ChessBoard::loadGameActivated, this, [&](){
        m_loadGameUI->reloadJsonFileList();
        setScene(m_loadGameUI);
    });
    connect(m_chessBoard, &ChessBoard::exitActivated, this, [&]() {
		close();
	});
    connect(m_chessBoard, &ChessBoard::newGameActivated, this, [&]() {
        m_mainMenu->sceneNum = sceneNum;
        m_mainMenu->curState = 1;
        m_mainMenu->hideAllButtons();
        m_mainMenu->setupState(1);
        setStyleSheet(QString("QGraphicsView { border-image: url(%1) 0 0 0 0 stretch stretch; }").arg(":/assets/backgroundimage/chessgame_menu.jpg"));
        setScene(m_mainMenu);
    });
}

void View::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Escape) {
		QApplication::quit();
	}
	else {
		QGraphicsView::keyPressEvent(event);
	}
}

View::~View() {
    // Delete dynamically allocated scenes
    // delete m_gameScene;
    // delete m_chessBoard;
    // delete m_mainMenu;
    // delete m_themesSetting;
    // delete m_settingsMenu;
    // delete m_loadGameUI;
}
