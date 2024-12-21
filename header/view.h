#pragma once

#include "utilities.h"
#include "chessboard.h"
#include "mainmenu.h"
#include "themesSetting.h"
#include "settingsMenu.h"
#include "loadgameui.h"
#include <QGraphicsView>
#include <QKeyEvent>


class View : public QGraphicsView
{
	Q_OBJECT
public:
	explicit View();
    ~View();
	static constexpr const int Width = 1000;
	static constexpr const int Height = 600;


protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
	GameScene* m_gameScene;
	ChessBoard* m_chessBoard;
	MainMenu* m_mainMenu;
	ThemesSetting* m_themesSetting;
	SettingsMenu* m_settingsMenu;
    LoadGameUI* m_loadGameUI;

    int sceneNum;

	QCursor customCursor;
};

