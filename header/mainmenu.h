#pragma once

#include "buttongame.h"
#include "svgbutton.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QCursor>
#include <QTimer>

class MainMenu : public QGraphicsScene {
	Q_OBJECT

public:
	MainMenu(QObject* parent = nullptr);
    ~MainMenu();
	int playerSide = 0, gameMode = 0, gameDifficulty = 0;
    void setupState(int);
    void hideState(int);
    void hideAllButtons(void);
    int sceneNum;
    int preState = 0, curState = 0;

signals:
	void playgameActivated();
	void loadgameActivated();
	void themeActivated();
	void settingsActivated();
	void exitActivated();
	void btnEasyClicked();
	void btnMediumClicked();
	void btnHardClicked();
    void backActivated();
    void mainMenuActivated();

private slots:
	void onPlayGameClicked();
	void onPvEClicked();
	void onBackClicked();

protected:

private:

	ButtonGame* btnPlayGame, * btnLoadGame, * btnThemes, * btnSettings, * btnExit;
	ButtonGame* btnPvP, * btnPvE;
	ButtonGame* btnEasy, * btnMedium, * btnHard;
    ButtonGame* btnBack, * btnMainMenu;

	std::vector<ButtonGame*> btnsState[3];
	std::vector<std::vector<ButtonGame*>> listBtn;

	QTimer * gameModeFlicker, * gameDifficultyFlicker, * playerSideFlicker;
	QGraphicsTextItem* gameTitle, * txtGameMode, * txtGameDifficulty, * txtPlayerSide;

    SvgButton* btnWhiteSide, * btnBlackSide, * btnRandomSide, * btnBackPreScene;

    bool isInMainMenuScene;
};

